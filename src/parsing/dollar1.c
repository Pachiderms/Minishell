/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	big_while(char c, int which)
{
	if (which == 0)
	{
		if (c != '$' && c != '?' && c != '=' && (c != '"')
			&& (c != '\'') && c != ' ' && c != ':' && !ft_isdigit(c) && c != '%'
			&& c != '\\' && c != ']' && c != '.' && c)
			return (0);
	}
	if (which == 1)
	{
		if (c != '$' && c != '?' && c != '=' && (c != '"')
			&& (c != '\'') && c != ' ' && c != ':' && c != '%'
			&& c != '\\' && c != ']' && c != '.' && c)
			return (0);
	}
	return (1);
}

char	*create_end_str(t_main *main, char *arg_dup)
{
	if (((arg_dup[main->dollars.i] == '"'
				&& main->d_qs[main->dollars.r1] == main->dollars.i)
			|| (arg_dup[main->dollars.i] == '\''
				&& main->s_qs[main->dollars.r] == main->dollars.i))
		&& arg_dup[main->dollars.i - 1] == '$')
		main->dollars.check = 1;
	if ((arg_dup[main->dollars.i] == '?'
			|| (arg_dup[main->dollars.i] >= '0'
				&& arg_dup[main->dollars.i] <= '9'))
		&& arg_dup[main->dollars.i - 1] == '$')
		main->dollars.i += 1;
	else if ((arg_dup[main->dollars.i] >= '0'
			&& arg_dup[main->dollars.i] <= '9')
		&& arg_dup[main->dollars.i - 1] != '$')
	{
		while (!big_while(main->dollars.arg_dup[main->dollars.i], 1))
			main->dollars.i++;
	}
	main->dollars.end = main->dollars.i;
	return (ft_substr(arg_dup, main->dollars.i,
			(ft_strlen(arg_dup) - main->dollars.i)));
}

void	free_tmps(t_main *main)
{
	if (main->dollars.tmp)
	{
		free(main->dollars.tmp);
		main->dollars.tmp = NULL;
	}
	if (main->dollars.tmp3)
	{
		free(main->dollars.tmp3);
		main->dollars.tmp3 = NULL;
	}
	if (main->dollars.tmp2)
	{
		free(main->dollars.tmp2);
		main->dollars.tmp2 = NULL;
	}
}

void	clear_dollar(t_main *main)
{
	if ((size_t)main->dollars.end == ft_strlen(main->dollars.arg_dup))
		main->dollars.i = main->dollars.end;
	else
	{
		arg_replace(&main->dollars.arg_dup, main->dollars.final_tmp);
		free(main->dollars.final_tmp);
		main->dollars.final_tmp = NULL;
		main->dollars.i = 0;
	}
	free_tmps(main);
	main->dollars.j = 0;
	main->dollars.end = 0;
	main->dollars.r = 0;
	main->dollars.r1 = 0;
	main->dollars.rep_pos = 0;
	main->dollars.check = 0;
}

int	begin_verif(char c, char cpl1, t_main *main)
{
	if (c == '$' && (cpl1 == ' ' || cpl1 == '=' || cpl1 == ':'
			|| (cpl1 == '"' && in_dquote(main,
					main->dollars.arg_dup, main->dollars.j) == 1)))
		return (1);
	return (0);
}
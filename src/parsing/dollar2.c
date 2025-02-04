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

int	in_dquote(t_main *main, char *arg_dup, int j)
{
	int	i;
	int	r1;
	int	begin;
	int	end;

	i = 0;
	r1 = 0;
	begin = 0;
	end = 0;
	while (main->d_qs[r1] != -1)
	{
		i = main->d_qs[r1];
		begin = i;
		i++;
		while (arg_dup[i] != '"')
			i++;
		end = i;
		if (j > begin && j < end)
			return (1);
		r1++;
	}
	return (0);
}

char	*fill_test(char *tmp, int size)
{
	int		i;
	int		j;
	char	*final;

	final = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] != '\\')
		{
			final[j] = tmp[i];
			j++;
		}
		i++;
	}
	final[j] = '\0';
	return (free(tmp), final);
}

void	del_backslash(char **final_tmp)
{
	int		i;
	int		bs;
	char	*tmp;

	i = 0;
	bs = 0;
	tmp = ft_strdup(*(final_tmp));
	while (tmp[i])
	{
		if (tmp[i] == '\\')
			bs++;
		i++;
	}
	free(*(final_tmp));
	*(final_tmp) = NULL;
	*final_tmp = fill_test(tmp, (i - bs));
}

void	search_sollar(t_main *main, char *arg_dup)
{
	if (main->dollars.j == main->s_qs[main->dollars.r])
	{
		main->dollars.j++;
		while (arg_dup[main->dollars.j] != '\'')
			main->dollars.j++;
		main->dollars.r++;
	}
	if (main->dollars.j == main->d_qs[main->dollars.r1])
		main->dollars.r1++;
	if (arg_dup[main->dollars.j] == '\\'
		&& arg_dup[main->dollars.j + 1] == '$')
		main->dollars.j += 2;
	main->dollars.j++;
	if (arg_dup[main->dollars.j] == '$'
		&& (arg_dup[main->dollars.j + 1] == ' '
			|| arg_dup[main->dollars.j + 1] == '='
			|| arg_dup[main->dollars.j + 1] == ':'
			|| ((arg_dup[main->dollars.j + 1] == '"'
					|| arg_dup[main->dollars.j + 1] == '\'')
				&& in_dquote(main, arg_dup, main->dollars.j) == 1)))
			main->dollars.j++;
}

void	create_and_replace_tmp2(t_main *main)
{
	if (ft_strcmp(main->dollars.tmp, main->dollars.arg_dup) != 0)
	{
		main->dollars.tmp2 = ft_substr(main->dollars.arg_dup,
				main->dollars.j, (main->dollars.end - main->dollars.j));
		main->dollars.rep_pos = check_var_exists2(main,
				&main->dollars.tmp2[1]);
		replace(main, &main->dollars.tmp2);
	}
}

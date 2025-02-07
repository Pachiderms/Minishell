/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:07:16 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 21:45:32 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_global_syntax(char *arg, t_main *main)
{
	int	i;
	int	j;

	i = 0;
	if (!arg)
		return (1);
	while (i < (int)ft_strlen(arg))
	{
		i += was_in_quotes(&arg[i], main,
				ft_substr(&arg[i], 0, ft_strlen(&arg[i])));
		if (i > (int)ft_strlen(arg))
			break ;
		if (ft_strncmp(&arg[i], "<<", 2) == 0
			|| ft_strncmp(&arg[i], ">>", 2) == 0
			|| ft_strncmp(&arg[i], "<>", 2) == 0)
			do_double_redirection(arg, main, i, &j);
		else if (ft_strncmp(&arg[i], "<", 1) == 0
			|| ft_strncmp(&arg[i], ">", 1) == 0)
			do_single_redirection(arg, main, i, &j);
		if (main->u_token)
			break ;
		i++;
	}
	return (main->u_token == NULL);
}

int	check_no_path(char *s, t_main *main)
{
	if (!s || s[0] == '\0'
		|| (((ft_strcmp(main->current_path, main->path) != 0))
			&& !check_builtin(s)))
		return (1);
	return (0);
}

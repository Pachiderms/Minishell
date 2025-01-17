/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/19 16:33:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	her_doc(t_main *main, char **split)
{
	char	*tmp;
	char	*res;
	char	*eof;
	int		fdout;

	(void)split;
	tmp = NULL;
	res = NULL;
	eof = main->tokens[main->hc_pos + 1].value;
	while (ft_strcmp(eof, tmp) != 0)
	{
		tmp = readline("heredoc> ");
		res = ft_strjoin_free(res, tmp);
		res = ft_strjoin_free(res, "\n");
		add_history(tmp);
	}
	fdout = get_fd_out(split);
	printf("fdout=%d\n", fdout);
	ft_putstr_fd(res, fdout);
	main->hc_pos = -1;
	return (0);
}
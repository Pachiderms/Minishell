/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:50:48 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/22 14:51:50 by tzizi            ###   ########.fr       */
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
	res = NULL;
	tmp = NULL;
	eof = main->tokens[main->hc_pos + 1].value;
	while (ft_strcmp(eof, tmp) != 0)
	{
		tmp = readline("heredoc> ");
		res = ft_strjoin_free(res, tmp, 0);
		res = ft_strjoin_free(res, "\n", 0);
		add_history(tmp);
	}
	fdout = get_fd_out(split);
	ft_putstr_fd(res, fdout);
	main->hc_pos = -1;
	return (0);
}

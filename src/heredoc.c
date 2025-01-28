/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/01/28 17:27:38 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int her_doc(t_main *main, char **split)
{
	char	*tmp;
	char	*res=NULL;
    char    *eof;

    (void)split;
    tmp = NULL;
    eof = main->tokens[main->hc_pos + 1].value;
	while (ft_strcmp(eof, tmp) != 0)
	{
		tmp = readline("heredoc> ");
		res = ft_strjoin_free(res, tmp, 0);
        res = ft_strjoin_free(res, "\n", 0);
		add_history(tmp);
    }
    int fdout = get_fd_out(split);
    printf("fdout=%d\n", fdout);
	ft_putstr_fd(res, fdout);
    main->hc_pos = -1;
	return (0);
}

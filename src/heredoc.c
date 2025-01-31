/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/01/31 13:10:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int write_in_here_doc(int here_doc, char *eof)
{
    char    *tmp;
    char    *res;

    res = NULL;
    while (1)
	{
        tmp = NULL;
		tmp = readline("heredoc> ");
        if (!tmp)
            return(free(res), 0);
        if (!ft_strcmp(eof, tmp))
            break ;
		res = ft_strjoin_free(res, tmp, 0);
        res = ft_strjoin_free(res, "\n", 0);
		add_history(tmp);
        free(tmp);
    }
    free(tmp);
	ft_putstr_fd(res, here_doc);
    close(here_doc);
    return(0);
}

int her_doc(t_main *main)
{
    char    *eof;
    int     here_doc;

    eof = main->tokens[main->hc_pos + 1].value;
    here_doc = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (here_doc < 0)
        return (-1);
    if (!write_in_here_doc(here_doc, eof))
    {
        unlink("heredoc.tmp");
        main->hc_pos = -1;
        return (-1);
    }
    main->hc_pos = -1;
	return (here_doc);
}

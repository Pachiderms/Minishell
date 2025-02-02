/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/01 17:59:39 by marvin           ###   ########.fr       */
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
    return(1);
}

int ft_heredoc(t_cmd *token)
{
    int     here_doc;

    if (!token->heredoc_eof)
        return (token->infile);
    here_doc = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (here_doc < 0)
        return (-1);
    if (!write_in_here_doc(here_doc, token->heredoc_eof))
    {
        unlink("heredoc.tmp");
        return (token->infile);
    }
    else
    {
        token->hd = 1;
        token->args = ft_strjoin_free(token->args, "heredoc.tmp", 0);
    }
    return (here_doc);
}

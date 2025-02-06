/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:36:53 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/06 16:59:41 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_node(t_cmd *node)
{
	if (!node)
		return ;
	if (node->cmd)
		free(node->cmd);
	if (node->args)
		free(node->args);
	if (node->infile > 0)
		close(node->infile);
	if (node->outfile > 1)
		close(node->outfile);
	if (node->heredoc_eof)
		free(node->heredoc_eof);
	if (node->args)
	node->cmd = NULL;
	node->args = NULL;
	node->heredoc_eof = NULL;
	node->next = NULL;
}

void	ft_lstclear(t_cmd **lst)
{
	if (*lst == NULL)
		return ;
	else if ((*lst)->next == NULL)
	{
		ft_lstdelone(*lst);
		*lst = NULL;
	}
	else
	{
		ft_lstclear(&(*lst)->next);
		ft_lstdelone(*lst);
		*lst = NULL;
	}
}

void	ft_lstdelone(t_cmd *lst)
{
	if (!lst)
		return ;
	clear_node(lst);
	free(lst);
}

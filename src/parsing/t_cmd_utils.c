/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:12:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/31 16:12:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_t_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
	{
		printf("fdin %d fdout %d heredoc '%s' cmd '%s' args '%s'\n",
			cmd->infile, cmd->outfile, cmd->heredoc_eof, cmd->cmd, cmd->args);
		cmd = cmd->next;
	}
	printf("fdin %d fdout %d heredoc '%s' cmd '%s' args '%s'\n", cmd->infile,
		cmd->outfile, cmd->heredoc_eof, cmd->cmd, cmd->args);
}

void	ft_lstadd_front(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	temp = *lst;
	*lst = new;
	new->next = temp;
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

t_cmd	*ft_lstnew(t_main *main, char **cmd)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	node->cmd = find_cmd(cmd, main);
	node->args = find_args(cmd, main);
	node->infile = -1;
	node->outfile = get_fd_out(cmd, main);
	node->heredoc_eof = find_heredoc_eof(cmd);
	node->next = NULL;
	return (node);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	else if (lst->next == NULL)
		return (lst);
	else
		return (ft_lstlast(lst->next));
}

int	ft_lstsize(t_cmd *lst)
{
	if (lst == NULL)
		return (0);
	else if (lst->next == NULL)
		return (1);
	else
		return (1 + ft_lstsize(lst->next));
}

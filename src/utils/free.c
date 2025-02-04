/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:36:53 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 02:45:53 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_process(t_main *main, int exit_code)
{
	// free_end_cmd(main);
	free_all_data(main);
	exit (exit_code);
}

void	free_end_cmd(t_main *main)
{
	ft_lstclear(&main->cmd_tokens);
	if (access("heredoc.tmp", F_OK) == 0)
		unlink("heredoc.tmp");
}

void	free_split(char **split)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (!split)
		return ;
	len = get_dchar_len(split);
	if (len <= 0)
		return ;
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

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
	node->cmd = NULL;
	node->args = NULL;
	node->heredoc_eof = NULL;
    node->next = NULL;
}

void    ft_lstclear(t_cmd **lst)
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
void    ft_lstdelone(t_cmd *lst)
{
    clear_node(lst);
    free(lst);
}

void	free_all_data(t_main *main)
{
	if (main->env)
		free_env(main->env, main->env_len);
	if (main->export)
		free_env(main->export, main->export_len);
	printf("HERE\n");
	if (main->cmd_no_quotes)
	{
		printf("FREEING1\n");
		free(main->cmd_no_quotes);
	}
	if (main->cmd_quotes)
	{
		printf("FREEING1\n");
		free(main->cmd_quotes);
	}
	ft_lstclear(&main->cmd_tokens);
}

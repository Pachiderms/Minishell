/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:08:42 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 21:08:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_builtin(t_main *main, t_cmd *token)
{
	redirect_in_out(token);
	rl_clear_history();
	init_signals();
	builtin(main);
	free_process(main, main->last_exit_code);
}

void	child_process(t_main *main, t_cmd *token)
{
	char	**split_args;
	char	*cmd;

	if (!token->cmd)
		free_process(main, 2);
	if (check_builtin(token->cmd))
		child_builtin(main, token);
	cmd = cook_cmd(token->cmd);
	token->infile = ft_heredoc(token, 0, main);
	token->args = rm_redirections(token, token->cmd, 0, main);
	split_args = ft_split(token->args, ' ');
	redirect_in_out(token);
	rl_clear_history();
	init_signals();
	execve(cmd, split_args, main->env);
	free(cmd);
	free_split(split_args);
	perror("execve");
	free_process(main, 1);
}

void	parent_process(t_cmd *token)
{
	close(token->pip[1]);
	if (token->infile >= 0)
		close(token->infile);
	if (token->next && token->next->infile < 0)
		token->next->infile = token->pip[0];
	else
		close(token->pip[0]);
}

int	exec_solo(t_main *main)
{
	t_cmd	*token;

	token = main->cmd_tokens;
	if (main->lastcmd < 0)
			return (1);
	while (token && main->lastcmd > 1)
	{
		main->lastcmd--;
		token = token->next;
	}
	ft_lstclear(&token->next);
	if (!token)
		return (1);
	if (pipe(token->pip) == -1)
		return (-1);
	exec_cmd(main, token);
	wait_solo(main);
	return (1);
}

int	exec(t_main *main, int solo)
{
	t_cmd	*token;

	token = main->cmd_tokens;
	if (!token)
		return (1);
	if (solo)
		return (exec_solo(main));
	while (token)
	{
		if (pipe(token->pip) == -1)
			return (-1);
		exec_cmd(main, token);
		token = token->next;
	}
	wait_all(main);
	return (1);
}

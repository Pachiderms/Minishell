/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec42.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:08:42 by marvin            #+#    #+#             */
/*   Updated: 2025/02/06 16:16:55 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	g_signal_pid;

void	wait_all(t_main *main)
{
	int		status;
	int		pid;
	int		len;
	t_cmd	*token;

	token = main->cmd_tokens;
	len = main->nb_cmd;
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				main->last_exit_code = WEXITSTATUS(status);
		}
		if (token->outfile >= 0)
			close(token->outfile);
		if (token->infile >= 0)
			close(token->infile);
		token = token->next;
	}
}

void	wait_solo(t_main *main)
{
	int		status;
	int		pid;
	t_cmd	*token;

	token = main->cmd_tokens;
	pid = waitpid(0, &status, 0);
	if (pid == g_signal_pid)
	{
		if (WIFEXITED(status))
			main->last_exit_code = WEXITSTATUS(status);
	}
	if (token->outfile >= 0)
		close(token->outfile);
	if (token->infile >= 0)
		close(token->infile);
}

void	redirect_in_out(t_cmd *token)
{
	close(token->pip[0]);
	if (token->infile >= 0)
	{
		dup2(token->infile, 0);
		close(token->infile);
	}
	if (token->outfile >= 0)
	{
		dup2(token->outfile, 1);
		close(token->outfile);
	}
	if (token->next)
		dup2(token->pip[1], 1);
	close(token->pip[1]);
}

int	exec_cmd(t_main *main, t_cmd *token)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all_data(main);
	else if (!g_signal_pid)
	{
		if (token->cmd)
			child_process(main, token);
		else
			free_all_data(main);
	}
	else
		parent_process(token);
	return (1);
}

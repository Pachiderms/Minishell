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

#include "../includes/minishell.h"

pid_t	g_signal_pid;

char	*prep_process(char *s, char *cmd)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = NULL;
	if (ft_strchr(s, '<') || ft_strchr(s, '>'))
	{
		res = get_rid_of_spaces(s);
		tmp = get_rid_of(res, '<');
		free(res);
		res = get_rid_of(tmp, '>');
		free(tmp);
		tmp = get_rid_of_spaces(res);
		if (cmd)
			tmp = ft_strjoin_free(" ", tmp, 1);
		return (free(res), ft_strjoin_free(cmd, tmp, 1));
	}
	res = get_rid_of_spaces(s);
	if (cmd)
		res = ft_strjoin_free(" ", res, 1);
	return (ft_strjoin_free(cmd, res, 1));
}

char	*cook_cmd(char *s)
{
	if (!s)
		return (NULL);
	if (!ft_strncmp(s, "/bin/", 5))
		return (ft_strdup(s));
	else if (!ft_strncmp(s, "/usr/bin/", 9))
		return (ft_strdup(s));
	else
		return (ft_strjoin("/usr/bin/", s));
}

static void	wait_all(t_main *main)
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

static void	redirect_in_out(t_cmd *token)
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

void	child_builtin(t_main *main, t_cmd *token)
{
	int	exit_code;

	redirect_in_out(token);
	rl_clear_history();
	init_signals();
	exit_code = builtin(main);
	free_process(main, exit_code);
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
	printf("cmd <%s>\n", cmd);
	token->args = prep_process(token->args, token->cmd);
	token->infile = ft_heredoc(token);
	printf("token fdin %d\n", token->infile);
	printf("final args <%s>\n", token->args);
	split_args = ft_split(token->args, ' ');
	redirect_in_out(token);
	rl_clear_history();
	init_signals();
	execve(cmd, split_args, main->env);
	free(cmd);
	free_split(split_args);
	perror("ERROR CHILD");
	free_process(main, 1);
}

static void	parent_process(t_cmd *token)
{
	close(token->pip[1]);
	if (token->infile >= 0)
		close(token->infile);
	if (token->next && token->next->infile < 0)
		token->next->infile = token->pip[0];
	else
		close(token->pip[0]);
}

static int	exec_cmd(t_main *main, t_cmd *token)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all_data(main);
	else if (!g_signal_pid)
	{
		if (token)
			child_process(main, token);
		else
			free_all_data(main);
	}
	else
		parent_process(token);
	return (1);
}

int 	exec(t_main *main)
{
	t_cmd	*token;

	token = main->cmd_tokens;
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

int	launch_process(t_main *main)
{
	return (exec(main));
}

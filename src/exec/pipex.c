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

void	child_process(t_main *main, char **cmd, int *pip);

char	*prep_process(char *s)
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
		return (free(res), tmp);
	}
	return (get_rid_of_spaces(s));
}
static void	parent_process(t_main *data, char **cmd, int *pip)
{
	close(pip[1]);
	if (data->infile >= 0)
		close(data->infile);
	if (data->infile == -2)
		data->infile = pip[0];
	if (*(cmd + 1))
		data->infile = pip[0];
	else
		close(pip[0]);
}

int g_signal_pid ;

static int	exec_cmd(t_main *data, char **cmd, int *pip)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all_data(data);
	else if (!g_signal_pid)
	{
		if (*cmd)
			child_process(data, cmd, pip);
		else
			free_all_data(data);
	}
	else
		parent_process(data, cmd, pip);
	return (1);
}

static void	wait_all(t_main *data)
{
	int		status;
	int		pid;
	int		len;
	char **tmp;

	tmp = data->split;
	len = data->nb_cmd;
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				data->last_exit_code = WEXITSTATUS(status);
		}
	}
	if (data->outfile >= 0)
		close(data->outfile);
	if (data->infile >= 0)
		close(data->infile);
}

int 	exec(t_main *data)
{
	char	**tmp;
	int		*pip;
	int i;

	i  = 1;
	pip = data->pip;
	tmp = data->split;
	if (pipe(pip) == -1)
		return (0);
	exec_cmd(data, tmp, pip);
	while (tmp[i])
	{
		if (pipe(pip) == -1)
			return (-1);
		exec_cmd(data, tmp, pip);
		i++;
	}
	wait_all(data);
	return (1);
}
int	ft_exec(t_main *main, char **cmd)
{
	int		fileout;
	char	**process;
	char	*_cmd;
	char	*tmp;

	if (check_builtin(cmd[0]))
		return (builtin(main, cmd, cmd[0]));
	// printf("cmd exec: %s\n", cmd[0]);
	_cmd = get_rid_of(cmd[0], '<');
	process = ft_split(_cmd, ' ');
	tmp = prep_process(_cmd);
	fileout = get_fd_out(process);
	if (fileout < 0)
		return (free_split(process), free(tmp), perror("fd"), 1);
	process = ft_split(tmp, ' ');
	free(tmp);
	free(_cmd);
	dup2(fileout, STDOUT_FILENO);
	tmp = ft_strjoin("/usr/bin/", process[0]);
	execve(tmp, process, main->env);
	exit(EXIT_FAILURE);
}

int	ft_fork(t_main *main, char **cmd)
{
	pid_t	fork_id;
	int		exit_code;

	fork_id = fork();
	exit_code = 0;
	if (fork_id == 0)
	{
		exit_code = ft_exec(main, cmd);
	}
	else
	{
		waitpid(fork_id, NULL, 0);
	}
	return (exit_code);
}

static void	redirect_in_out(t_main *main, char **cmd, int *pip)
{
	close(pip[0]);
	if (main->infile >= 0)
	{
		dup2(main->infile, 0);
		close(main->infile);
	}
	if (main->outfile >= 0)
	{
		dup2(main->outfile, 1);
		close(main->outfile);
	}
	else if (*(cmd + 1) != NULL)
		dup2(pip[1], 1);
	close(pip[1]);
}

void	child_process(t_main *main, char **cmd, int *pip)
{
	char	**path;
	char *ok;

	ok = prep_process(*(cmd));
	path = ft_split(ok, ' ');
	free(ok);
	ok = ft_strjoin("/usr/bin/", path[0]);
	main->last_exit_code = 1;
	redirect_in_out(main, cmd, pip);
	rl_clear_history();
	init_signals();
	execve(ok, path, main->env);
	free_all_data(main);
	perror("ERROR CHILD");
	exit(0);
}
//pourquoi ca marche tout seul mais pas la ?????

int	launch_process(t_main *main, char **processes)
{
	int	exit_code;

	if (main->nb_cmd < 2)
		exit_code = ft_fork(main, processes);
	else
		exit_code = exec(main);
	return (free_split(processes), exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:08:42 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 21:08:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	child_process2(t_main *main, char *cmd, int *fd)
{
	char	**tmp;
	char	*_cmd;
	char	*cm;

	close(fd[0]);
	_cmd = prep_process(cmd);
	tmp = ft_split(_cmd, ' ');
	cm = ft_strjoin("/usr/bin/", tmp[0]);
	dup2(fd[1], STDOUT_FILENO);
	execve(cm, tmp, main->env);
	exit(EXIT_FAILURE);
}

int	ft_pipe2(t_main *main, char **processes)
{
	int		i;
	pid_t	child_pid;
	int		fd[2];
	int		fdin;

	i = 0;
	if (pipe(fd) < 0)
		return (perror("pipe fail"), 1);
	fdin = get_fd_in(&processes[i]);
	dup2(fdin, STDIN_FILENO);
	while (i < main-> nb_cmd - 1)
	{
		child_pid = fork();
		if (child_pid < 0)
			return (perror("fork fail"), 1);
		if (!child_pid)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			ft_exec(main, &processes[i]);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
		i++;
	}
	int exit_code = ft_fork(main, &processes[i]);
	return (exit_code);
}

int	launch_process(t_main *main, char **processes)
{
	int	exit_code;
	if (main->nb_cmd < 2)
		exit_code = ft_fork(main, processes);
	else
		exit_code = ft_pipe2(main, processes);
	return (free_split(processes), exit_code);
}

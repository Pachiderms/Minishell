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
	char	**process;
	char	*_cmd;
	char	*tmp;

	in_and_out(main, cmd, NULL);
	_cmd = get_rid_of(cmd[0], '<');
	process = ft_split(_cmd, ' ');
	tmp = prep_process(*cmd);
	process = ft_split(tmp, ' ');
	free(tmp);
	free(_cmd);
	tmp = ft_strjoin("/usr/bin/", process[0]);
	execve(tmp, process, main->env);
	perror("exec");
	free_split(process);
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

void	in_and_out(t_main *main, char **cmd, int *fd)
{
	main->fdin = get_fd_in(cmd);
	main->fdout = get_fd_out(cmd);
	if (fd)
		close(fd[0]);
	if (main->fdin > 0)
	{
		dup2(main->fdin, STDIN_FILENO);
	}
	if (main->fdout > 1)
	{
		dup2(main->fdout, STDOUT_FILENO);
	}
	if (*(cmd + 1))
	{
		dup2(fd[1], STDOUT_FILENO);
	}
	if (fd)
		close (fd[1]);
}

void	child_process(t_main *main, char **cmd, int *fd)
{
	char	*command;
	char	**lcmd;

	in_and_out(main, cmd, fd);
	command = prep_process(*cmd);
	lcmd = ft_split(command, ' ');
	free(command);
	command = ft_strjoin("/usr/bin/", lcmd[0]);
	if (check_builtin(lcmd[0]))
	{
		main->last_exit_code = builtin(main, cmd, cmd[0]);
		return (free(command), free_split(lcmd));
	}
	execve(command, lcmd, main->env);
	perror("exec child");
	free_split(cmd);
	free_split(lcmd);
	free(command);
	exit(EXIT_FAILURE);
}

void	parent_process(char **cmd, int *fd)
{
	if (*(cmd + 1))
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	add_pid(t_main *main, int pid)
{
	int	*last;
	int	nb_pid;
	int	i;

	i = 0;
	nb_pid = 0;
	last = main->pids;
	while (main->pids[i] != -1)
	{
		if (pid == main->pids[i])
			return ;
		nb_pid++;
		i++;
	}
	i = 0;
	main->pids = NULL;
	main->pids = malloc((nb_pid + 2) * sizeof(int));
	while (last[i] != -1)
	{
		main->pids[i] = last[i];
		i++;
	}
	main->pids[i] = pid;
	main->pids[i + 1] = -1;
	i = 0;
}

void	run_pipex(t_main *main, char **cmd, int *fd)
{
	int	fork_id;

	fork_id = fork();
	if (fork_id < 0)
		return (perror("fork fail"));
	if (fork_id == 0)
	{
		child_process(main, cmd, fd);
	}
	parent_process(cmd, fd);
	add_pid(main, fork_id);
}

void	ft_wait(t_main *main)
{
	int	i;

	i = 0;
	while (main->pids[i] != -1)
	{
		waitpid(main->pids[i], NULL, 0);
		i++;
	}
}

int	ft_pipe(t_main *main, char **cmd)
{
	int	fd[2];
	int	i;

	i = -1;
	while (++i < main->nb_cmd)
	{
		if (pipe(fd) < 0)
			return (perror("pipe fail"), 1);
		run_pipex(main, &cmd[i], fd);
	}
	ft_wait(main);
	return (0);
}
//pourquoi ca marche tout seul mais pas la ?????

int	launch_process(t_main *main, char **processes)
{
	int	exit_code;

	if (main->nb_cmd < 2)
		exit_code = ft_fork(main, processes);
	else
		exit_code = ft_pipe(main, processes);
	return (free_split(processes), exit_code);
}

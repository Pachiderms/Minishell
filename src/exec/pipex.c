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

int PROCESS_NUM;

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

void    close_pipes(int pipes[PROCESS_NUM][2], int me)
{
    int i;

    i = 0;
    while (i < PROCESS_NUM)
    {
        if (i != me)
            close(pipes[i][0]);
        // if (i + plus != no)
        close(pipes[i][1]);
        i++;
    }
}

void	close_all_pipes(int pipes[PROCESS_NUM + 1][2])
{
	int i;

    i = 0;
    while (i < PROCESS_NUM)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
}

void	ft_wait(int pids[PROCESS_NUM])
{
	int	i;

	i = 0;
	while (i < PROCESS_NUM)
		waitpid(pids[i], NULL, 0);
}

void	child_process(t_main *main, char *cmd, int pipes[PROCESS_NUM + 1][2], int i)
{
	dup2(pipes[i + 1][1], STDOUT_FILENO);
	// close_pipes(pipes, i, i + 1, 1);
	ft_exec(main, &cmd);
}

int	ft_pipe2(t_main *main, char **processes)
{
	pid_t	child_pid[main->nb_cmd];
	pid_t	fork_id;
	int		fd[main->nb_cmd][2];
	int		fdin;
	int		fdout;
	int		i;

	i = -1;
	while (++i < main->nb_cmd){
		if (pipe(fd) < 0)
			return (perror("pipe fail"), 1);
	}
	fdin = get_fd_in(&processes[0]);
	fdout = get_fd_out(&processes[main->nb_cmd - 1]);
	dup2(fdin, STDIN_FILENO);
	i = -1;
	while (++i < PROCESS_NUM)
	{
		child_pid[i] = fork();
		if (child_pid < 0)
			return (perror("fork fail"), 1);
		if (child_pid[i] == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			close(fdout);
			ft_exec(main, &processes[i]);
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	i = -1;
	while (++i < main->nb_cmd){
		waitpid(child_pid[i], NULL, 0);
	}
	fork_id = fork();
	if (fork_id == 0)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		close(fd[0]);
		close(fd[1]);
		ft_exec(main, &processes[i]);
	}
	close(fd[0]);
	close(fd[1]);
	close(fdout);
	waitpid(fork_id, NULL, 0);
	return (1);
}

int	launch_process(t_main *main, char **processes)
{
	int	exit_code;
	PROCESS_NUM = main->nb_cmd;
	if (main->nb_cmd < 2)
		exit_code = ft_fork(main, processes);
	else
		exit_code = ft_pipe2(main, processes);
	return (free_split(processes), exit_code);
}

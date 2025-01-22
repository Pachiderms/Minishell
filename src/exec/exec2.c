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

int	launch_process(t_main *main, char **processes)
{
	int	exit_code;

	if (main->nb_cmd < 2)
		exit_code = ft_fork(main, processes);
	return (free_split(processes), exit_code);
}

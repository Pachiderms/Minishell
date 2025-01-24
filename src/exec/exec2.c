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

static void	wait_all(t_main *main)
{
	int		status;
	int		pid;
	int		len;
	char	**tmp;

	tmp = main->split;
	len = main->nb_cmd;
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				main->last_exit_code = WEXITSTATUS(status);
		}
	}
	if (main->outfile >= 0)
		close(main->outfile);
	if (main->infile >= 0)
		close(main->infile);
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
		//close(main->outfile);
	}
	if (*(cmd + 1) != NULL)
		dup2(pip[1], 1);
	close(pip[1]);
}

void	child_builtin(t_main *main, char **cmd, int *pip)
{
	int	exit_code;

	redirect_in_out(main, cmd, pip);
	rl_clear_history();
	init_signals();
	exit_code = builtin(main, cmd, cmd[0]);
	free_process(main, exit_code);
}

void	child_process(t_main *main, char **cmd, int *pip)
{
	char	**path;
	char 	*ok;

	main->outfile = get_fd_out(cmd);
	ok = prep_process(*cmd);
	path = ft_split(ok, ' ');
	free(ok);
	if (!is_cmd(path[0], main->path))
	{
		free_split(path);
		free_process(main, 2);
	}
	if (check_builtin(path[0]))
		child_builtin(main, path, pip);
	free_split(path);
	if (ft_strrchr(*cmd, '>'))
		cut_str(*cmd, ft_strrchr(*cmd, '>'));
	ok = prep_process(*cmd);
	path = ft_split(ok, ' ');
	free(ok);
	ok = ft_strjoin("/usr/bin/", path[0]);
	redirect_in_out(main, cmd, pip);
	rl_clear_history();
	init_signals();
	execve(ok, path, main->env);
	perror("ERROR CHILD");
	free_process(main, 1);
}

static void	parent_process(t_main *main, char **cmd, int *pip)
{
	close(pip[1]);
	if (main->infile >= 0)
		close(main->infile);
	if (main->infile == -2)
		main->infile = pip[0];
	if (*(cmd + 1))
		main->infile = pip[0];
	else
		close(pip[0]);
}

static int	exec_cmd(t_main *main, char **cmd, int *pip)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all_data(main);
	else if (!g_signal_pid)
	{
		if (*cmd)
			child_process(main, cmd, pip);
		else
			free_all_data(main);
	}
	else
		parent_process(main, cmd, pip);
	return (1);
}

int 	exec(t_main *main)
{
	char	**tmp;
	int		*pip;
	int i;

	i  = 1;
	pip = main->pip;
	tmp = main->split;
	if (pipe(pip) == -1)
		return (0);
	exec_cmd(main, tmp, pip);
	while (tmp[i])
	{
		if (pipe(pip) == -1)
			return (-1);
		exec_cmd(main, &tmp[i], pip);
		i++;
	}
	wait_all(main);
	return (1);
}

int	launch_process(t_main *main)
{
	return (exec(main));
}

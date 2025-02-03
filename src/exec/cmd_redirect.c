/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:12:07 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/03 18:28:17 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_opening_outfile(char *file, int append)
{
	int		fd;

	fd = -1;
	if (append)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			return (-2);
		if (access(file, W_OK) != 0)
		{
			close(fd);
			return (-3);
		}
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (-2);
		if (access(file, W_OK) != 0)
		{
			close(fd);
			return (-3);
		}
	}
	return (fd);
}

int	handle_opening_infile(char *file, int heredoc)
{
	int		fd;

	fd = -1;
	if (heredoc) // heredoc
	{
		fd = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (-2);
		return (fd);
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (-2);
		if (access(file, R_OK) != 0)
		{
			close(fd);
			return (-3);
		}
	}
	return (fd);
}

char	*get_next(char **cmd, char *tf)
{
	if (ft_strcmp(*cmd, tf) == 0)
	{
		if (*(cmd + 1))
			return (*(cmd + 1));
	}
	else if (ft_strnstr(*cmd, tf, ft_strlen(*cmd)))
	{
		return (&ft_strrchr(*cmd, tf[0])[1]);
	}
	if (!ft_strcmp(tf, "<"))
		return (*cmd);
	return (NULL);
}

int	get_fd_out(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	if (cmd == NULL)
		return (fd);
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		if (get_next(&cmd[i], ">>"))
		{
			fd = handle_opening_outfile(get_next(&cmd[i], ">>"), 1);
		}
		else if (get_next(&cmd[i], ">"))
		{
			fd = handle_opening_outfile(get_next(&cmd[i], ">"), 0);
		}
		i++;
	}
	return (fd);
}

int	get_fd_in(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	if (cmd == NULL)
		return (fd);
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		if (get_next(&cmd[i], "<"))
		{
			if (fd > 0)
				close (fd);
			fd = handle_opening_infile(get_next(&cmd[i], "<"), 0);
		}
		i++;
	}
	return (fd);
}

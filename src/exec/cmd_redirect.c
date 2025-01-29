/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:12:07 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/20 15:07:14 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_opening_outfile(char *file, int append)
{
	int		fd;
	char	*tmp;

	fd = -1;
	tmp = get_rid_of_spaces(file);
	if (append)
	{
		fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			return (free(tmp), -1);
		if (access(tmp, W_OK) != 0)
		{
			close(fd);
			return (free(tmp), -1);
		}
	}
	else
	{
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (free(tmp), -1);
		if (access(tmp, W_OK) != 0)
		{
			close(fd);
			return (free(tmp), -1);
		}
	}
	return (free(tmp), fd);
}

int	handle_opening_infile(char *file, int append)
{
	int		fd;

	fd = -1;
	if (append) // heredoc
		return (-1);
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (access(file, R_OK) != 0)
		{
			close(fd);
			return (-1);
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
	return (NULL);
}

int	get_fd_out(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		if (get_next(&cmd[i], ">>"))
		{
			fd = handle_opening_outfile(get_next(&cmd[i], ">>"), 1);
		}
		if (get_next(&cmd[i], ">"))
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

	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_infile(cmd[i + 1], 0));
			return (-1);
		}
		i++;
	}
	return (0);
}

int	get_cmd_number(t_main *main, char **split)
{
	int	i;
	int	j;
	int	cmd;

	cmd = 0;
	i = 0;
	while (split[i])
	{
		if (is_cmd(split[i], main->path))
		{
			cmd++;
			j = i + 1;
			while (split[j])
			{
				if (ft_strcmp(split[j], "|") == 0)
					break ;
				if (main->tokens[j].type == command)
					main->tokens[j].type = argument;
				j++;
			}
			i += (j - i - 1);
		}
		i++;
	}
	return (cmd);
}

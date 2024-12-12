/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:12:07 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/19 16:40:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_opening_file(char *file, int append)
{
	int	fd;

	fd = -1;
	if (append)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (access(file, W_OK) != 0)
			return (-1);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (access(file, W_OK) != 0)
			return (-1);
	}
	return (fd);
}

int	get_fd(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && ft_strcmp(cmd[i], "|") != 0)
	{
		if (ft_strcmp(cmd[i], ">>") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_file(cmd[i + 1], 1));
			return (-1);
		}
		if (ft_strcmp(cmd[i], ">") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_file(cmd[i + 1], 0));
			return (-1);
		}
		i++;
	}
	return (1);
}


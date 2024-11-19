/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:06:47 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/18 17:06:47 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_prompt(char **cmd, int nl)
{
	int	i;

	i = 1;
	if (!nl)
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
}

void	echo_file(char **cmd, int fd, int nl)
{
	int	i;

	i = 1;
	if (!nl)
		i++;
	while (cmd[i] && !is_sc(cmd[i]))
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", fd);
	close(fd);
}

void	ft_echo(char **cmd)
{
	int	fd;
	int	nl;

	nl = 1;
	fd = get_fd(cmd);
	if (fd < 0 || !cmd[1])
		return ;
	if (ft_strcmp(cmd[0], "echo") != 0)
		return ;
	if (ft_strcmp(cmd[1], "-n") == 0)
		nl = 0;
	if (fd > 1)
		echo_file(cmd, fd, nl);
	else
		echo_prompt(cmd, nl);
}

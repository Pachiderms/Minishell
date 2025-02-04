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

int	ft_echo(t_main *main)
{
	int			fd;
	char		*nl;

	nl = find_newline(main->cmd_tokens->args);
	fd = main->cmd_tokens->outfile;
	if (fd == -1)
		fd = 1;
	if (fd < 0)
		return (perror(GREY"minishell"), 1);
	if (nl)
		return (ft_putstr_fd(&nl[1], fd), 0);
	else
		return (ft_putendl_fd(main->cmd_tokens->args, fd), 0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:26:30 by tzizi            #+#    #+#             */
/*   Updated: 2024/11/18 20:26:30 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(t_main *main, char **split, char *cmd)
{
	(void)cmd;
	if (ft_strcmp(split[0], "env") == 0
		|| ft_strcmp(split[0], "/bin/env") == 0)
		return (print_env(main, 0, split));
	if (ft_strcmp(split[0], "export") == 0)
		return (prep_export(main, split));
	if (ft_strcmp(split[0], "unset") == 0)
		return (prep_unset(main, split));
	if (ft_strcmp(split[0], "echo") == 0)
		return (ft_echo(main, split));
	if (ft_strcmp(split[0], "cd") == 0
		|| ft_strcmp(split[0], "/bin/cd") == 0)
		return (cd(main, split));
	if (ft_strcmp(split[0], "pwd") == 0)
		return (pwd(main, split));
	if (ft_strcmp(split[0], "exit") == 0)
	{
		printf("exit\n");
		free_process(main, -42);
	}
	return (1);
}

int	ft_process(t_main *main, char *cmd)
{
	main->split = prep_cmd_exec(main);
	if (main->hc_pos >= 0)
		her_doc(main, main->split);
	else if (main->nb_cmd >= 1)
	{
		if (main->nb_cmd == 1)
		{
			if (check_builtin(main->base_split[0]))
				return (builtin(main, main->base_split, main->cmd));
		}
		main->last_exit_code = launch_process(main);
		main->nb_cmd = 0;
	}
	else if (cmd[0] != '\0')
		printf(GREY"minishell: %s: command not found\n"RESET,
			main->tokens[0].value);
	return (1);
}

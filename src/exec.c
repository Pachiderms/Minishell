/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+          */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:23:24 by tzizi            #+#    #+#              */
/*   Updated: 2025/01/17 17:23:24 by tzizi           ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin(t_main *main, char **split, char *cmd)
{
	(void)cmd;
	if (ft_strcmp(main->tokens[0].value, "env") == 0
		|| ft_strcmp(main->tokens[0].value, "/bin/env") == 0)
		main->last_exit_code = print_env(main, 0, split);
	if (ft_strcmp(main->tokens[0].value, "export") == 0)
		main->last_exit_code = prep_export(main, split);
	if (ft_strcmp(main->tokens[0].value, "unset") == 0)
		main->last_exit_code = prep_unset(main, split);
	if (ft_strcmp(main->tokens[0].value, "echo") == 0)
		main->last_exit_code = ft_echo(main, split);
	if (ft_strcmp(main->tokens[0].value, "cd") == 0)
		main->last_exit_code = cd(main, split);
	if (ft_strcmp(main->tokens[0].value, "pwd") == 0)
		main->last_exit_code = pwd(main, split);
}

int	ft_exec(t_main *main, char **split, char *cmd)
{
	if (main->hc_pos >= 0)
		her_doc(main, split);
	else if (main->nb_cmd >= 1)
	{
		if (check_builtin(main->tokens[0].value)
			&& main->nb_cmd == 1)
			builtin(main, split, cmd);
		else
		{
			if (check_var_exists(main->env, main->env_len, "export PATH=") == -1)
				return (printf("minishell: %s: No such file or directory\n", split[0]), 1);
			main->last_exit_code = prep_cmd_pipex(main, split);
		}
		main->nb_cmd = 0;
	}
	else if (cmd[0] != '\0')
		printf(GREY"minishell: %s: command not found\n"RESET,
			main->tokens[0].value);
	return (1);
}

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

char	**prep_builtin(t_cmd *token)
{
	char	*join;
	char	**res;

	join = ft_strjoin(token->cmd, " ");
	join = ft_strjoin_free(join, token->args, 0);
	res = ft_split(join, ' ');
	return (free(join), res);
}

int	builtin(t_main *main)
{
	char	*command;
	char	**split;

	main->nb_cmd = 0;
	split = prep_builtin(main->cmd_tokens);
	command = get_cmd(main->cmd_tokens->cmd);
	if (ft_strcmp(command, "env") == 0)
		main->last_exit_code = print_env(main, 0, split);
	if (ft_strcmp(command, "export") == 0)
		main->last_exit_code = prep_export(main, split);
	if (ft_strcmp(command, "unset") == 0)
		main->last_exit_code = prep_unset(main, main->cmd_tokens->args);
	if (ft_strcmp(command, "echo") == 0)
		main->last_exit_code = ft_echo(main, split);
	if (ft_strcmp(command, "cd") == 0)
		main->last_exit_code = cd(main, split);
	if (ft_strcmp(command, "pwd") == 0)
		main->last_exit_code = pwd(main, split);
	if (ft_strcmp(command, "exit") == 0)
	{
		printf("exit\n");
		free_process(main, -42);
	}
	return (1);
}

int	no_cmd(t_main *main)
{
	if (ft_strchr(main->cmd_tokens->args, '/'))
	{
		if (chdir(main->cmd_tokens->args) == 0)
		{
			printf(GREY"minishell: %s: Is a directory\n"RESET,
				main->cmd_tokens->args);
			return_to_pwd(main);
			return (126);
		}
		else
			printf(GREY"minishell: %s: No such file or directory\n"RESET,
				main->cmd_tokens->args);
	}
	else
		printf(GREY"minishell: %s: command not found\n"RESET,
			main->cmd_tokens->args);
	return (127);
}

int	ft_process(t_main *main)
{
	t_cmd	*cmd_tokens;

	// if (main->unexpected_token)
	
	printf("nb cmd %d\n", main->nb_cmd);
	cmd_tokens = main->cmd_tokens;
	if (!ft_strcmp(cmd_tokens->cmd, "cat") || !ft_strcmp(cmd_tokens->cmd, "sleep"))
		cat = 1;
	if (main->nb_cmd >= 1)
	{
		if (main->nb_cmd == 1)
		{
			if (check_builtin(cmd_tokens->cmd))
				return (builtin(main));
		}
		main->last_exit_code = launch_process(main);
		main->nb_cmd = 0;
	}
	else if (cmd_tokens->args)
		main->last_exit_code = no_cmd(main);
	return (1);
}

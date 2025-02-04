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

void	builtin(t_main *main)
{
	char	*command;

	main->nb_cmd = 0;
	if (main->cmd_tokens->heredoc_eof)
			main->cmd_tokens->infile = ft_heredoc(main->cmd_tokens, 1, main);
	printf("args enter builtin <%s>\n", main->cmd_tokens->args);
	command = get_cmd(main->cmd_tokens->cmd);
	main->cmd_tokens->args = rm_redirections(main->cmd_tokens,
			main->cmd_tokens->cmd, 1);
	printf("args before builtin <%s>\n", main->cmd_tokens->args);
	if (ft_strcmp(command, "env") == 0)
		main->last_exit_code = print_env(main, 0);
	if (ft_strcmp(command, "export") == 0)
		main->last_exit_code = prep_export(main);
	if (ft_strcmp(command, "unset") == 0)
		main->last_exit_code = prep_unset(main);
	if (ft_strcmp(command, "echo") == 0)
		main->last_exit_code = ft_echo(main);
	if (ft_strcmp(command, "cd") == 0)
		main->last_exit_code = cd(main);
	if (ft_strcmp(command, "pwd") == 0)
		main->last_exit_code = pwd(main);
	if (ft_strcmp(command, "exit") == 0)
	{
		printf("exit\n");
		free_process(main, -42);
	}
}

int	no_cmd(t_main *main)
{
	if (main->cmd_tokens->heredoc_eof)
		ft_heredoc(main->cmd_tokens, 1, main);
	else if (ft_strchr(main->cmd_tokens->args, '/'))
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
			main->arg[0]);
	return (127);
}

int	ft_process(t_main *main)
{
	t_cmd	*cmd_tokens;

	if (main->u_token)
	{
		main->last_exit_code = 2;
		if (main->last_ofile)
			unlink(main->last_ofile);
		printf("minishell: syntax error near unexpected token `%s'\n", main->u_token);
		return (1);
	}
	printf("nb cmd %d\n", main->nb_cmd);
	cmd_tokens = main->cmd_tokens;
	if (!ft_strcmp(cmd_tokens->cmd, "cat")
		|| !ft_strcmp(cmd_tokens->cmd, "sleep"))
		cat = 1;
	if (main->nb_cmd >= 1)
	{
		if (main->nb_cmd == 1)
		{
			if (check_builtin(cmd_tokens->cmd))
			{
				builtin(main);
				return (1);
			}
		}
		main->last_exit_code = exec(main);
		main->nb_cmd = 0;
	}
	else if (cmd_tokens->args || cmd_tokens->heredoc_eof)
		main->last_exit_code = no_cmd(main);
	return (1);
}

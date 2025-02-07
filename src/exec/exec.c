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

int	nof_builtin(t_main *main, t_cmd *token)
{
	if (token->no_file)
	{
		if (was_in_quotes(token->args, main, ft_strdup(token->args)) > 0)
			return (0);
		main->last_exit_code = ft_nosfod("file", token->no_file);
		return (1);
	}
	return (0);
}

int	exit_code(t_main *main, t_cmd *token, char *command)
{
	if (ft_strcmp(command, "env") == 0)
		return (print_env(main, 0, token));
	if (ft_strcmp(command, "export") == 0)
		return (prep_export(main, token));
	if (ft_strcmp(command, "unset") == 0)
		return (prep_unset(main));
	if (ft_strcmp(command, "echo") == 0)
		return (ft_echo(main, token));
	if (ft_strcmp(command, "cd") == 0)
		return (cd(main, token));
	if (ft_strcmp(command, "pwd") == 0)
		return (pwd(main, token));
	return (1);
}

void	builtin(t_main *main, t_cmd *token)
{
	char	*command;

	main->nb_cmd--;
	if (token->heredoc_eof)
			token->infile = ft_heredoc(token, 1);
	if (nof_builtin(main, token))
		return ;
	command = get_cmd(token->cmd);
	token->args = rm_redirections(token,
			token->cmd, 1, main);
	main->last_exit_code = exit_code(main, token, command);
	if (ft_strcmp(command, "exit") == 0)
	{
		printf("exit\n");
		if (token->args && ft_strcmp(token->args, "exit") != 0)
		{
			main->last_exit_code = ft_exit(main, token);
			if (main->last_exit_code >= 0 && main->last_exit_code <= 255)
				free_process(main, main->last_exit_code);
			else if (main->last_exit_code == -1)
				main->last_exit_code = 1;
		}
		else
			free_process(main, 0);
	}
}

int	ft_process(t_main *main)
{
	int	no;

	no = no_cmd(main);
	if (no)
		return (exec(main, 1));
	if (!main->current_path && main->cmd_tokens->cmd
		&& !check_builtin(main->cmd_tokens->cmd))
		return (ft_error("nsfod", main->cmd_tokens->cmd));
	update_gpid(main);
	if (main->nb_cmd >= 1)
	{
		if (main->nb_cmd == 1)
		{
			if (check_builtin(main->cmd_tokens->cmd))
			{
				builtin(main, main->cmd_tokens);
				return (1);
			}
		}
		exec(main, 0);
		main->nb_cmd = 0;
	}
	return (1);
}

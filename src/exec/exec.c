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

void	builtin(t_main *main, t_cmd *token)
{
	char	*command;

	main->nb_cmd--;
	if (token->heredoc_eof)
			token->infile = ft_heredoc(token, 1);
	if (token->no_file)
	{
		main->last_exit_code = ft_error("nosfod", token->no_file);
		return ;
	}
	command = get_cmd(token->cmd);
	token->args = rm_redirections(token,
			token->cmd, 1, main);
	if (token->no_file)
		main->last_exit_code = ft_error("nosfod", token->no_file);
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
		if (token->args && ft_strcmp(token->args, "exit") != 0)
		{
			main->last_exit_code = ft_exit(main);
			if (main->last_exit_code >= 0 && main->last_exit_code <= 255)
				free_process(main, main->last_exit_code);
			else if (main->last_exit_code == -1)
				main->last_exit_code = 1;
		}
		else
			free_process(main, -42);
	}
}

int	no_cmd(t_main *main)
{
	t_cmd	*token;
	int		error;
	int		i;

	token = main->cmd_tokens;
	error = 0;
	i = 0;
	while (token)
	{
		i++;
		if (!token->cmd)
		{
			if (token->heredoc_eof)
				ft_heredoc(token, 1);
			else if (token->no_file)
				main->last_exit_code = ft_error("nosfod", token->no_file);
			else if (ft_strchr(token->args, '/'))
			{
				if (chdir(token->args) == 0)
				{
					return_to_pwd(main);
					main->last_exit_code = ft_error("dir", token->args);
					error = 1;
				}
				else
				{
					main->last_exit_code = ft_error("nosfod", token->args);
					error = 1;
				}
			}
			else
			{
				main->last_exit_code = ft_error("cnf", token->args);
				error = 1;
			}
		}
		else
			main->lastcmd = i;
		token = token->next;
	}
	return (error);
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
	if (!ft_strcmp(main->cmd_tokens->cmd, "cat")
		|| !ft_strcmp(main->cmd_tokens->cmd, "/bin/cat")
		|| !ft_strcmp(main->cmd_tokens->cmd, "/bin/sleep")
		|| !ft_strcmp(main->cmd_tokens->cmd, "sleep")
		|| !ft_strcmp(main->cmd_tokens->cmd, "grep")
		|| !ft_strcmp(main->cmd_tokens->cmd, "/bin/grep"))
		g_signal_pid = 1;
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

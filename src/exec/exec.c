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
	command = get_cmd(main->cmd_tokens->cmd);
	main->cmd_tokens->args = rm_redirections(main->cmd_tokens,
			main->cmd_tokens->cmd, 1, main);
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
	t_cmd	*token;

	token = main->cmd_tokens;
	while (token)
	{
		if (main->cmd_tokens->heredoc_eof)
			ft_heredoc(main->cmd_tokens, 1, main);
		else if (ft_strchr(token->args, '/'))
		{
			if (chdir(token->args) == 0)
			{
				return_to_pwd(main);
				main->last_exit_code = ft_error("dir", token->args);
			}
			else
			{
				main->last_exit_code = ft_error("nosfod", token->args);
			}
		}
		else
			main->last_exit_code = ft_error("cnf", token->args);
		token = token->next;
	}
	return (0);
}

int	u_ttoken(t_main *main)
{
	main->last_exit_code = 2;
	if (main->last_ofile)
		unlink(main->last_ofile);
	return (ft_error("serr", main->u_token));
}

int	ft_process(t_main *main)
{
	if (main->u_token)
		return (u_ttoken(main));
	if (no_cmd(main))
		return (1);
	if (!main->current_path && main->cmd_tokens->cmd
		&& !check_builtin(main->cmd_tokens->cmd))
		return (ft_error("nsfod", main->cmd_tokens->cmd));
	if (!ft_strcmp(main->cmd_tokens->cmd, "cat")
		|| !ft_strcmp(main->cmd_tokens->cmd, "sleep"))
		g_cat = 1;
	if (main->nb_cmd >= 1)
	{
		if (main->nb_cmd == 1)
		{
			if (check_builtin(main->cmd_tokens->cmd))
			{
				builtin(main);
				return (1);
			}
		}
		exec(main);
		main->nb_cmd = 0;
	}
	return (1);
}

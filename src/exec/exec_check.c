/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:56:04 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 19:49:51 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dir_or_file(t_main *main, t_cmd *token)
{
	if (chdir(token->args) == 0)
	{
		return_to_pwd(main);
		main->last_exit_code = ft_error("dir", token->args);
		return (1);
	}
	else
	{
		main->last_exit_code = ft_nosfod("dir", token->args);
		return (1);
	}
	return (0);
}

int	nocmd_error(t_main *main, t_cmd *token)
{
	if (token->heredoc_eof)
		ft_heredoc(token, 1);
	if (main->nofile)
	{
		main->last_exit_code = ft_nosfod("file", main->nofile);
		return (1);
	}
	else if (token->no_file)
	{
		main->last_exit_code = ft_nosfod("file", token->no_file);
		return (1);
	}
	else if (ft_strchr(token->args, '/'))
		return (dir_or_file(main, token));
	else
	{
		main->last_exit_code = ft_error("cnf", token->args);
		return (1);
	}
	return (0);
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
			error = nocmd_error(main, token);
		}
		else
			main->lastcmd = i;
		token = token->next;
	}
	return (error);
}

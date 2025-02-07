/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:34:46 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 18:33:17 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_nosfod(char *type, char *msg)
{
	if (!ft_strcmp(type, "dir"))
	{
		printf("minishell: %s: No such file or directory\n", msg);
		return (127);
	}
	else if (!ft_strcmp(type, "file"))
	{
		if (access(msg, X_OK) == -1)
		{
			printf("minishell: %s: Permission denied\n", msg);
			return (126);
		}
		printf("minishell: %s: No such file or directory\n", msg);
		return (1);
	}
	return (1);
}

int	ft_error(char *type, char *msg)
{
	if (!ft_strcmp(type, "dir"))
	{
		printf("minishell: %s: Is a directory\n", msg);
		return (126);
	}
	else if (!ft_strcmp(type, "cnf"))
	{
		if (msg)
			printf("minishell: %s: command not found\n", msg);
		else
			printf("minishell: : command not found\n");
		return (127);
	}
	else if (!ft_strcmp(type, "serr"))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", msg);
		return (2);
	}
	else if (!ft_strcmp(type, "evnf"))
	{
		return (printf("minishell: ‘%s’: event not found\n", msg), 0);
	}
	return (1);
}

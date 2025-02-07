/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:34:46 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 12:21:05 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_export(char *type, char *msg)
{
	if (!ft_strcmp(type, "nvid"))
	{
		printf("minishell: export: ‘%s’: not a valid identifier\n", msg);
		return (0);
	}
	else if (!ft_strcmp(type, "env"))
	{
		printf("env: ‘%s’: No such file or directory\n", msg);
		return (0);
	}
	else if (!ft_strcmp(type, "io"))
	{
		printf("minishell: export: -%c: invalid option\n", msg[0]);
		return (0);
	}
	return (0);
}

int	ft_error_unset(char *type, char *msg)
{
	if (!ft_strcmp(type, "nvid"))
	{
		printf("minishell: unset: ‘%s’: not a valid identifier\n", msg);
		return (0);
	}
	else if (!ft_strcmp(type, "io"))
	{
		printf("minishell: unset: -%c: invalid option\n",
			msg[0]);
		return (0);
	}
	return (0);
}

int	ft_error_cd(char *type, char *msg)
{
	if (!ft_strcmp(type, "io"))
	{
		printf("minishell: cd: -%c: invalid option\n", msg[0]);
		return (0);
	}
	if (!ft_strcmp(type, "tma"))
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!ft_strcmp(type, "home"))
	{
		printf("minishell: cd: HOME not set\n");
		return (0);
	}
	if (!ft_strcmp(type, "nsfod"))
	{
		printf("minishell: cd: %s: No such file or directory\n", msg);
		return (1);
	}
	return (0);
}

int	ft_error_pwd(char *type, char *msg)
{
	if (!ft_strcmp(type, "big"))
	{
		printf("pwd: error retrieving current directory: getcwd ");
		printf("cannot access parent directories: ");
		printf("No such file or directory\n");
		return (0);
	}
	else if (!ft_strcmp(type, "io"))
	{
		printf("minishell: pwd: -%c: invalid option\n", msg[0]);
		return (0);
	}
	return (0);
}

int	ft_nosfod(char *type, char *msg)
{
	if (!ft_strcmp(type, "dir"))
	{
		printf("minishell: %s: No such file or directory\n", msg);
		return (127);
	}
	else if (!ft_strcmp(type, "file"))
	{
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
		printf("minishell: %s: command not found\n", msg);
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

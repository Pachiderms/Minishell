/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:34:46 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 19:29:13 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error_ex(char *type, char *msg)
{
	if (!ft_strcmp(type, "nvid"))
	{
		printf("minishell: export: ‘%s’: not a valid identifier\n", msg);
		return (0);
	}
	return (0);
}

int	ft_error(char *type, char *msg)
{
	if (!ft_strcmp(type, "dir"))
	{
		printf(GREY"minishell: %s: Is a directory\n"RESET, msg);
		return (126);
	}
	else if (!ft_strcmp(type, "nosfod"))
	{
		printf(GREY"minishell: %s: No such file or directory\n"RESET, msg);
		return (127);
	}
	else if (!ft_strcmp(type, "cnf"))
	{
		printf(GREY"minishell: %s: command not found\n"RESET, msg);
		return (127);
	}
	else if (!ft_strcmp(type, "serr"))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", msg);
		return (1);
	}
	else if (!ft_strcmp(type, "nvid"))
	{
		//export
		printf("minishell: export: ‘%s’: not a valid identifier\n", msg);
		return (0);
	}
	else if (!ft_strcmp(type, "evnf"))
	{
		printf("minishell: ‘%s’: event not found\n", msg);
		return (0);
	}
	else if (!ft_strcmp(type, "nvid"))
	{
		//unset
		printf("minishell: unset: ‘%s’: not a valid identifier\n", msg);
		return (0);
	}
	else if (!ft_strcmp(type, "io"))
	{
		printf("minishell: unset: -%c: invalid option\n", msg[0]);
		return (0);
	}
	return (1);
}

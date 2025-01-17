/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:08:43 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:08:45 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	actual_arg_size(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '/')
	{
		while (arg[i])
			i++;
	}
	else
	{
		while (arg[i] != '/' && arg[i])
			i++;
	}
	return (i);
}

void	fill_actual_arg(char *actual_arg, char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '/')
	{
		while (arg[i])
		{
			actual_arg[i] = arg[i];
			i++;
		}
	}
	else
	{
		while (arg[i] != '/' && arg[i])
		{
			actual_arg[i] = arg[i];
			i++;
		}
	}
	actual_arg[i] = '\0';
}

void	*handle_home_case(t_main *main, char *actual_arg)
{
	int	home_pos;

	if (ft_strcmp(actual_arg, "--") == 0)
	{
		free(actual_arg);
		actual_arg = NULL;
		home_pos = check_var_exists(main->env, main->env_len, "export HOME=");
		if (home_pos == -1)
		{
			printf("bash: cd: HOME not set\n");
			return (NULL);
		}
		actual_arg = ft_strdup(&ft_strchr(main->env[home_pos], '=')[1]);
	}
	else if (ft_strcmp(actual_arg, "~") == 0
		|| ft_strcmp(actual_arg, "~/") == 0)
	{
		free(actual_arg);
		actual_arg = NULL;
		actual_arg = ft_strdup("/home/zamgar");
	}
	return ("not null");
}

char	*get_actual_arg(t_main *main, char *arg)
{
	char	*actual_arg;
	int		oldpwd_pos;

	actual_arg = (char *)malloc(sizeof(char) * (actual_arg_size(arg) + 1));
	fill_actual_arg(actual_arg, arg);
	if (ft_strcmp(actual_arg, "-") == 0)
	{
		free(actual_arg);
		actual_arg = NULL;
		oldpwd_pos = check_var_exists(main->env, main->env_len,
				"export OLDPWD=");
		actual_arg = ft_strdup(&ft_strchr(main->env[oldpwd_pos], '=')[1]);
		printf("%s\n", actual_arg);
	}
	if (handle_home_case(main, actual_arg) == NULL)
		return (NULL);
	return (actual_arg);
}

int	is_special_case(char *actual_arg)
{
	if (ft_strcmp(actual_arg, "-") == 0)
		return (1);
	if (actual_arg[0] == '/')
		return (1);
	if (ft_strcmp(actual_arg, "--") == 0)
		return (1);
	if (ft_strcmp(actual_arg, "~") == 0 || ft_strcmp(actual_arg, "~/") == 0)
		return (1);
	return (0);
}

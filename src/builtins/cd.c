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

int	actualise_index(char *arg, char *actual_arg, int i)
{
	while (arg[i] != '/' && arg[i])
		i++;
	free(actual_arg);
	if (arg[i] == '/')
		i++;
	return (i);
}

int	handle_chdir(t_main *main, char *actual_arg, int chdir_value)
{
	if (chdir_value == -1)
	{
		if (return_to_pwd(main) == 0)
			return (0);
		return (ft_error_cd("nsfod", actual_arg));
	}
	return (1);
}

int	check_syntax_cd(t_main *main, char *arg)
{
	int		i;
	int		chdir_value;
	char	*actual_arg;
	int		special_case;

	i = 0;
	if (arg[0] == '-' && arg[1] && ft_strcmp(arg, "--") != 0)
		return (free(arg), ft_error_cd("io", &arg[1]));
	while (arg[i])
	{
		actual_arg = get_actual_arg(main, &arg[i]);
		if (actual_arg == NULL)
			return (0);
		special_case = is_special_case(&arg[i]);
		chdir_value = chdir(actual_arg);
		if (handle_chdir(main, actual_arg, chdir_value) == 0)
			return (free(actual_arg), 0);
		if (special_case == 1)
			return (1);
		i = actualise_index(arg, actual_arg, i);
	}
	return (1);
}

int	print_home_pwd(t_main *main)
{
	int	chdir_value;
	int	home_pos;

	chdir_value = 0;
	home_pos = 0;
	home_pos = check_var_exists(main->env, main->env_len, "export HOME=");
	if (home_pos == -1)
		return (ft_error_cd("home", NULL));
	chdir_value = chdir(&ft_strchr(main->env[home_pos], '=')[1]);
	if (chdir_value == -1)
		return (0);
	if (chdir_value == 0)
		return (update_oldpwd_pwd(main), 1);
	return (0);
}

int	cd(t_main *main)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (perror("getcwd"), free(dir), 1);
	if (get_arg_len(main->cmd_tokens->args) >= 2)
			return (free(dir), ft_error_cd("tma", NULL));
	if (!main->cmd_tokens->args)
	{
		if (print_home_pwd(main) == 1)
			return (free(dir), 0);
	}
	else
	{
		if (check_syntax_cd(main, main->cmd_tokens->args) == 1)
		{
			update_oldpwd_pwd(main);
			return (free(dir), 0);
		}
	}
	return (free(dir), 1);
}

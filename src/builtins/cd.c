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
		return (printf("minishell: cd: %s: No such file or directory\n"
				, actual_arg), 0);
	}
	return (1);
}

int	check_syntax_cd(t_main *main, char *arg) // trop de lignes
{
	int		i;
	int		chdir_value;
	char	*actual_arg;
	int		special_case;

	i = 0;
	if (arg[0] == '-' && arg[1] && ft_strcmp(arg, "--") != 0)
		return (printf("minishell: cd: -%c: invalid option\n", arg[1]), free(arg), 0);
	while (arg[i])
	{
		actual_arg = get_actual_arg(main, &arg[i]);
		if (actual_arg == NULL)
			return (0);
		special_case = is_special_case(&arg[i]);
		chdir_value = chdir(actual_arg);
		if (handle_chdir(main, actual_arg, chdir_value) == 0)
			return (0);
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
	{
		printf("minishell: cd: HOME not set\n");
		return (0);
	}
	chdir_value = chdir(&ft_strchr(main->env[home_pos], '=')[1]);
	if (chdir_value == -1)
		return (0);
	if (chdir_value == 0)
		return (update_oldpwd_pwd(main), 1);
	return (0);
}

int	cd(t_main *main, char **split)
{
	char	*dir;
	/* chdir_value = chdir("");
	char *pwd = getcwd(NULL, 0);
	printf("pwd : %s\n", pwd);
	printf("chdir_value : %d\n", chdir_value);
	exit(0); */
	dir = getcwd(NULL, 0);
	if (!dir)
		return (perror("getcwd"), free(dir), 1);
	if (main->split_len > 2)
		return (printf("minishell: cd: too many arguments\n"), free(dir), 0);
	if (main->split_len == 1 && (ft_strcmp("cd", split[0]) == 0 || ft_strcmp("/bin/cd", split[0]) == 0))
	{
		if (print_home_pwd(main) == 1)
			return (free(dir), 1);
	}
	else
	{
		if (check_syntax_cd(main, split[1]) == 1)
		{
			update_oldpwd_pwd(main);
			return (free(dir), 1);
		}
	}
	return (free(dir), 0);
}
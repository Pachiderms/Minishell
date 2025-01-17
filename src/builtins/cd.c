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

int	return_to_pwd(t_main *main)
{
	int		pwd_pos;
	int		chdir_value;
	char	*pwd_value;

	pwd_pos = check_var_exists(main->env, main->env_len, "export PWD=");
	pwd_value = &ft_strchr(main->env[pwd_pos], '=')[1];
	chdir_value = chdir(pwd_value);
	if (chdir_value == -1)
		return (0);
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
		return (printf("bash: cd: -%c: invalid option\n", arg[1]), free(arg), 0);
	while (arg[i])
	{
		actual_arg = get_actual_arg(main, &arg[i]);
		if (actual_arg == NULL)
			return (0);
		special_case = is_special_case(&arg[i]);
		chdir_value = chdir(actual_arg);
		if (chdir_value == -1)
		{
			if (return_to_pwd(main) == 0)
				return (0);
			//if ((ft_strcmp(main->env[pwd_pos], "PWD=/") == 0) && (ft_strcmp(actual_arg, "..") != 0))
			return (printf("bash: cd: %s: No such file or directory\n"
					, actual_arg), 0);
		}
		if (special_case == 1)
			return (1);
		while (arg[i] != '/' && arg[i])
			i++;
		free(actual_arg);
		if (arg[i] == '/')
			i++;
	}
	return (1);
}

void	update_oldpwd_pwd(t_main *main)
{
	int		pwd_line;
	char	*pwd;
	char	*newpwd;

	pwd_line = check_var_exists(main->env, main->env_len, "export PWD=");
	pwd = ft_strdup(&ft_strchr(main->env[pwd_line], '=')[1]);
	export(main, ft_strjoin("export OLDPWD=", pwd));
	free(pwd);
	newpwd = ft_strdup(getcwd(NULL, 0));
	export(main, ft_strjoin("export PWD=", newpwd));
	free(newpwd);
	return ;
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
		printf("bash: cd: HOME not set\n");
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
	/* chdir_value = chdir("");
	char *pwd = getcwd(NULL, 0);
	printf("pwd : %s\n", pwd);
	printf("chdir_value : %d\n", chdir_value);
	exit(0); */
	if (getcwd(NULL, 0) == NULL)
		return (printf("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"), 1);
	if (main->split_len > 2)
		return (printf("bash: cd: too many arguments\n"), 0);
	if (main->split_len == 1 && ft_strcmp("cd", split[0]) == 0)
	{
		if (print_home_pwd(main) == 1)
			return (1);
	}
	else
	{
		if (check_syntax_cd(main, split[1]) == 1)
		{
			update_oldpwd_pwd(main);
			return (1);
		}
	}
	return (0);
}

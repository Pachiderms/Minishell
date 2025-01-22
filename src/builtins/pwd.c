/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:19 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/23 14:09:26 by marvin           ###   ########.fr       */
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

void	update_oldpwd_pwd(t_main *main)
{
	int		pwd_line;
	char	*pwd;
	char	*newpwd;

	pwd_line = check_var_exists(main->env, main->env_len, "export PWD=");
	pwd = ft_strjoin("export OLDPWD=", &ft_strchr(main->env[pwd_line], '=')[1]);
	export(main, pwd);
	free(pwd);
	newpwd = ft_strjoin_free("export PWD=", getcwd(NULL, 0), 1);
	export(main, newpwd);
	free(newpwd);
	return ;
}

int	check_syntax_pwd(char *cmd)
{
	if (cmd[0] == '-')
		return (printf("bash: pwd: -%c: invalid option\n", cmd[1]), 0);
	return (1);
}

int	pwd(t_main *main, char **cmd)
{
	char	*pwd;

	if (main->split_len == 2)
	{
		if (check_syntax_pwd(cmd[1]) == 0)
			return (0);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (free(pwd), printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"), 0);
	printf("%s\n", pwd);
	return (free(pwd), 1);
}

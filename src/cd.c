#include "../includes/minishell.h"

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

int	cd(t_main *main, char *cmd)
{
	int		chdir_value;
	char	*arg;

	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	chdir_value = chdir(arg);
	if (chdir_value == 0)
		return (free(arg), update_oldpwd_pwd(main), 0);
	return (free(arg), 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:04:53 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/07 16:38:59 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset_var(t_main *main, char *cmd)
{
	char	*_cmd;
	char	*tmp2;

	_cmd = ft_strdup(cmd);
	tmp2 = cut_str(&ft_strchr(_cmd, ' ')[1], ft_strchr(cmd, '='));
	tmp2 = ft_strjoin("unset ", tmp2);
	free(_cmd);
	unset(main, tmp2);
	free(tmp2);
	return (-1);
}

void	ok(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg [i - 1] == '+')
		arg[i - 1] = '\0';
	else
		arg[i] = '\0';
}

int	check_var_exists(char **env, int len, char *cmd)
{
	int		i;
	int		j;
	char	*arg;
	char	*actual_var;

	i = 0;
	j = 0;
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	ok(arg);
	while (i < len)
	{
		if (ft_strncmp(env[i], "export ", 7) == 0)
			actual_var = ft_strdup(&ft_strchr(env[i], ' ')[1]);
		else
			actual_var = ft_strdup(env[i]);
		while (actual_var[j] != '=' && actual_var[j])
			j++;
		actual_var[j] = '\0';
		if (ft_strcmp(arg, actual_var) == 0)
			return (free(arg), free(actual_var), i);
		free(actual_var);
		j = 0;
		i++;
	}
	return (free(arg), -1);
}

void	unset_env(t_main *main, char *cmd)
{
	int		i;
	int		j;
	int		var_to_unset;
	char	**tmp;

	i = 0;
	j = 0;
	var_to_unset = check_var_exists(main->env, main->env_len, cmd);
	if (var_to_unset == -1)
		return ;
	tmp = (char **)malloc(sizeof(char *) * (main->env_len + 1));
	remake_env(tmp, main, 0, -2);
	while (i < main->env_len)
	{
		if (i == var_to_unset)
			i++;
		main->env[j] = ft_strdup(tmp[i]);
		i++;
		j++;
		if (i == var_to_unset)
			i++;
	}
	main->env[j] = NULL;
	free_env(tmp, main->env_len);
	main->env_len -= 1;
}

void	unset_export(t_main *main, char *cmd)
{
	int		i;
	int		j;
	int		var_to_unset;
	char	**tmp;

	i = 0;
	j = 0;
	var_to_unset = check_var_exists(main->export, main->export_len, cmd);
	if (var_to_unset == -1)
		return ;
	tmp = (char **)malloc(sizeof(char *) * (main->export_len + 1));
	remake_env(tmp, main, 1, -2);
	while (i < main->export_len)
	{
		if (i == var_to_unset)
			i++;
		main->export[j] = ft_strdup(tmp[i]);
		i++;
		j++;
		if (i == var_to_unset)
			i++;
	}
	main->export[j] = NULL;
	free_env(tmp, main->export_len);
	main->export_len -= 1;
}

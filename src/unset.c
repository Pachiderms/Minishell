/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:04:53 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:04:55 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_unset(t_main *main, char **split)
{
	int i;
	char *tmp;

	i = 1;
	while (split[i] && is_sc(split[i]) != 1)
	{
		tmp = ft_strjoin("unset ", split[i]);
		unset(main, tmp);
		free(tmp);
		i++;	
	}
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
	while (arg[i] != '=' && arg[i])
		i++;
	arg[i] = '\0';
	//printf("'%s'\n\n", arg);
	i = 0;
	while (i < len)
	{
		actual_var = ft_strdup(env[i]);
		while (actual_var[j] != '=' && actual_var[j])
			j++;
		actual_var[j] = '\0';
		//printf("'%s'\n", actual_var);
		if (ft_strcmp(arg, actual_var) == 0)
			return (free(arg), free(actual_var), i);
		free(actual_var);
		actual_var = NULL;
		j = 0;
		i++;
	}
	free(arg);
	return (-1);
}

int	check_syntax_unset(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	if (ft_strncmp(cmd, "unset ", 6) != 0)
		return (0);
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	if (ft_strncmp(arg, "_", -1) == 0)
		return (free(arg), 0);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (free(arg), 0);
		i++;
	}
	free(arg);
	return (1);
}

void	unset(t_main *main, char *cmd)
{
	int		i;
	int		j;
	int		var_to_unset;
	char	**tmp;

	i = 0;
	j = 0;
	if (check_syntax_unset(cmd) == 0)
		return ;
	var_to_unset = check_var_exists(main->env, main->env_len, cmd);
	if (var_to_unset == -1)
		return ;
	tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
	while (i < main->env_len)
	{
		tmp[i] = ft_strdup(main->env[i]);
		i++;
	}
	free_env(main->env, main->env_len);
	main->env = (char **)malloc(sizeof(char *) * (main->env_len - 1) + 1);
	i = 0;
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
	free_env(tmp, main->env_len);
	main->env_len -= 1;
	return ;
}

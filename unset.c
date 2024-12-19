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
	if (arg [i - 1] == '+')
		arg[i - 1] = '\0';
	else
		arg[i] = '\0';
	i = 0;
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
		actual_var = NULL;
		j = 0;
		i++;
	}
	free(arg);
	return (-1);
}

int	check_var_exists2(t_main *main, char *arg)
{
	int		i;
	int		j;
	char	*actual_var;

	i = 0;
	j = 0;
	while (i < main->env_len)
	{
		actual_var = ft_strdup(main->env[i]);
		while (actual_var[j] != '=')
			j++;
		actual_var[j] = '\0';
		if (ft_strcmp(arg, actual_var) == 0)
			return (free(actual_var), i);
		free(actual_var);
		actual_var = NULL;
		j = 0;
		i++;
	}
	return (-1);
}

int	unset_env(char **env, int env_len, char *cmd)
{
	int		i;
	int		j;
	int		var_to_unset;
	char	**tmp;

	i = 0;
	j = 0;
	var_to_unset = check_var_exists(env, env_len, cmd);
	if (var_to_unset == -1)
		return (0);
	tmp = (char **)malloc(sizeof(char *) * (env_len + 1));
	remake_env(tmp, env, env_len, -2);
	while (i < env_len)
	{
		if (i == var_to_unset)
			i++;
		env[j] = ft_strdup(tmp[i]);
		i++;
		j++;
		if (i == var_to_unset)
			i++;
	}
	env[j] = NULL;
	free_env(tmp, env_len);
	return (1) ;
}

int	check_syntax_unset(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	if (arg[0] == '_' && arg[1] == '\0')
		return (0);
	if (arg[0] == '\0' || ft_isdigit(arg[0]) == 1)
		return (printf("bash: unset: ‘%s’: not a valid identifier\n", arg), 0);
	if (arg[0] == '-' && arg[1])
		return (printf("bash: unset: -%c: invalid option\n", arg[1]), 0);
	while (arg[i++])
	{
		if (arg[i] == '=' || arg[i] == '?' || arg[i] == '.'
		|| arg[i] == '+' || arg[i] == '{' || arg[i] == '}'
		|| arg[i] == '-' || arg[i] == '*' || arg[i] == '#'
		|| arg[i] == '@' || arg[i] == '^' || arg[i] == '~')
			return (printf("bash: unset: ‘%s’: not a valid identifier\n", arg), 0);
	}
	i = 0;
	while (arg[i++])
	{
		if (arg[i] == '!')
			return (printf("bash: %s: event not found\n", ft_strchr(arg, '!')), 0);
	}
	return (1);
} // trop de lignes

void	unset(t_main *main, char *cmd)
{
	if (check_syntax_unset(cmd) == 0)
		return ;
	if (unset_env(main->env, main->env_len, cmd) == 1)
		main->env_len -= 1;
	if (unset_env(main->export, main->export_len, cmd) == 1)
		main->export_len -= 1;
	printf("Env Len : %d | Export Len : %d\n", main->env_len, main->export_len);
	return ;
}

void	prep_unset(t_main *main, char **split)
{
	int i;
	char *tmp;

	i = 1;
	while (split[i] && is_sc(split[i]) != 1)
	{
		printf("split : '%s'\n", split[i]); //
		tmp = ft_strjoin("unset ", split[i]);
		unset(main, tmp);
		free(tmp);
		i++;	
	}
	return ;
}
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

void	print_ascii_order(t_main *main)
{
	int		i;
	char	*tmp;
	char	**sort_env;
	int		sortenv_len;

	i = 0;
	sortenv_len = main->env_len - 1;
	sort_env = (char **)malloc(sizeof(char *) * sortenv_len + 1);
	while (i < sortenv_len)
	{
		sort_env[i] = ft_strdup(main->env[i]);
		i++;
	}
	i = 0;
	while (i < sortenv_len - 1)
	{
		if (ft_strncmp(sort_env[i], sort_env[i + 1], -1) > 0)
		{
			tmp = sort_env[i + 1];
			sort_env[i + 1] = sort_env[i];
			sort_env[i] = tmp;
			i = 0;
		}
		i++;
	}
	tmp = sort_env[1];
	sort_env[1] = sort_env[0];
	sort_env[0] = tmp;
	i = 0;
	while (i < sortenv_len)
	{
		printf("%s\n", sort_env[i]);
		i++;
	}
	free_env(sort_env, sortenv_len);
	//printf("Env Len : %d\n", (main->env_len));
}

void	prep_export(t_main *main, char **split)
{
	int i;
	char *tmp;

	i = 1;
	if (ft_strcmp(split[0], "export") == 0 && split[1] == NULL)
	{
		print_ascii_order(main);
		return ;
	}
	while (split[i] && is_sc(split[i]) != 1)
	{
		tmp = ft_strjoin("export ", split[i]);
		export(main, tmp);
		free(tmp);
		i++;	
	}
}

int	check_syntax_export(t_main *main, char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	if (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", -1) == 0)
		return (print_ascii_order(main), 0);
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	if (arg[0] == '_' && arg[1] == '=')
		return (free(arg), 0);
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg[i - 1] == ' ' || i == 0 || arg[i] == '\0')
		return (free(arg), 0);
	free(arg);
	return (1);
}

void	export(t_main *main, char *cmd)
{
	int		i;
	char	**tmp;
	int		replace_pos;

	i = 0;
	if (check_syntax_export(main, cmd) == 0)
		return ;
	replace_pos = check_var_exists(main, cmd);
	tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
	while (i < main->env_len)
	{
		tmp[i] = ft_strdup(main->env[i]);
		i++;
	}
	free_env(main->env, main->env_len);
	if (replace_pos >= 0)
		main->env = (char **)malloc(sizeof(char *) * (main->env_len) + 1);
	else
		main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1) + 1);
	i = 0;
	while (i < main->env_len)
	{
		if (i == replace_pos)
		{
			main->env[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			i++;
		}
		main->env[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			main->env[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			i++;
		}
	}
	free_env(tmp, main->env_len);
	if (replace_pos == -1)
	{
		main->env[i] = main->env[i - 1];
		main->env[i - 1] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
		main->env_len += 1;
	}
	//printf("Env Len : %d\n", (main->env_len));
	return ;
}
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

void	print_ascii_order(t_main *main) // a voir
{
	int		i;
	char	*tmp;
	char	**sort_env;

	i = 0;
	sort_env = (char **)malloc(sizeof(char *) * main->env_len + 1);
	while (i < main->env_len)
	{
		sort_env[i] = ft_strdup(main->env[i]);
		i++;
	}
	i = 0;
	while (i < main->env_len - 1)
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
	i = 0;
	while (i < main->env_len)
	{
		if (!(sort_env[i][0] == '_' && sort_env[i][0] == '=')) // faire en sorte de ne pas afficher le _= et de trouver cmment bouger le SSH_AUTH_SOCK en haut
			printf("%s\n", sort_env[i]);
		i++;
	}
	free_old_env(sort_env, main->env_len);
}

int	check_syntax_export(t_main *main, char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	if (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", -1) == 0)
		return (print_ascii_order(main), 0);
	if (ft_strncmp(cmd, "export ", 7) != 0)
		return (0);
	arg = ft_strdup(ft_strchr(cmd, ' '));
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
	free_old_env(main->env, main->env_len);
	if (replace_pos >= 0)
		main->env = (char **)malloc(sizeof(char *) * (main->env_len) + 1);
	else
		main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1) + 1);
	i = 0;
	while (i < main->env_len)
	{
		if (i == replace_pos)
		{
			main->env[i] = ft_strdup(ft_strchr(cmd, ' '));
			i++;
		}
		main->env[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			main->env[i] = ft_strdup(ft_strchr(cmd, ' '));
			i++;
		}
	}
	free_old_env(tmp, main->env_len);
	if (replace_pos == -1)
	{
		main->env[i] = main->env[i - 1];
		main->env[i - 1] = ft_strdup(ft_strchr(cmd, ' '));
		main->env_len += 1;
	}
	return ;
}

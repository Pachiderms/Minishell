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

void	remake_env(char	**tmp, t_main *main, int which, int replace_pos) // trop de ligne
{
	int	i;

	i = 0;
	if (which == 0)
	{
		while (i < main->env_len)
		{
			tmp[i] = ft_strdup(main->env[i]);
			i++;
		}
		free_env(main->env, main->env_len);
		if (replace_pos >= 0)
			main->env = malloc(sizeof(char *) * ((main->env_len) + 1));
		else if (replace_pos == -1)
			main->env = malloc(sizeof(char *) * ((main->env_len + 1) + 1));
		else if (replace_pos == -2)
			main->env = malloc(sizeof(char *) * ((main->env_len - 1) + 1));
	}
	if (which == 1)
	{
		while (i < main->export_len)
		{
			tmp[i] = ft_strdup(main->export[i]);
			i++;
		}
		free_env(main->export, main->export_len);
		if (replace_pos >= 0)
			main->export = malloc(sizeof(char *) *((main->export_len) + 1));
		else if (replace_pos == -1)
			main->export = malloc(sizeof(char *) *((main->export_len + 1) + 1));
		else if (replace_pos == -2)
			main->export = malloc(sizeof(char *) *((main->export_len - 1) + 1));
	}
	return ;
}

char	*create_replace_pos(char *cmd)
{
	char	*save_value;
	char	*temp;

	if (ft_strchr(cmd, '='))
	{
		save_value = ft_strjoin(ft_strjoin("\"", &ft_strchr(cmd, '=')[1]), "\""); // ft_strdup enleve norme
		temp = save_value;
		save_value = ft_strjoin("export ", ft_strjoin(get_var_name(cmd), temp));
		free(temp);
		return (save_value);
	}
	else
		return (ft_strjoin("export ", &ft_strchr(cmd, ' ')[1]));
}

void	add_pos(t_main *main, char *cmd, int i, int which)
{
	if (which == 0)
	{
		main->env[i] = main->env[i - 1];
		main->env[i - 1] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
		main->env_len += 1;
	}
	else if (which == 1)
	{
		main->export[i] = main->export[i - 1];
		main->export[i - 1] = create_replace_pos(cmd);
		main->export_len += 1;
	}
	return ;
}

void	fill_env_export(t_main *main, char *cmd)
{
	int		i;
	int		replace_pos;
	char	**tmp;

	i = 0;
	replace_pos = check_var_exists(main->env, main->env_len, cmd);
	tmp = (char **)malloc(sizeof(char *) * (main->env_len + 1));
	remake_env(tmp, main, 0, replace_pos);
	if (replace_pos >= 0)
		main->env[replace_pos] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	while (i < main->env_len)
	{
		if (i == replace_pos)
			i++;
		main->env[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
			i++;
	}
	main->env[i] = NULL;
	free_env(tmp, main->env_len);
	if (replace_pos == -1)
		add_pos(main, cmd, i, 0);
	fill_export(main, cmd);
}

void	fill_export(t_main *main, char *cmd)
{
	int		i;
	int		replace_pos;
	char	**tmp;

	i = 0;
	replace_pos = check_var_exists(main->export, main->export_len, cmd);
	tmp = (char **)malloc(sizeof(char *) * (main->export_len + 1));
	remake_env(tmp, main, 1, replace_pos);
	if (replace_pos >= 0)
		main->export[replace_pos] = create_replace_pos(cmd);
	while (i < main->export_len)
	{
		if (i == replace_pos)
			i++;
		main->export[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
			i++;
	}
	main->export[i] = NULL;
	free_env(tmp, main->export_len);
	if (replace_pos == -1)
		add_pos(main, cmd, i, 1);
}

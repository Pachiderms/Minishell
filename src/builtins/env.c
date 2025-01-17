/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:10:51 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:10:52 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(char **tab, int tablen)
{
	int	i;

	i = tablen - 1;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	tab = NULL;
	return ;
}

void	print_ascii_order(t_main *main) // trop de lignes
{
	int		i;
	char	*tmp;
	char	**sort_env;

	i = 0;
	sort_env = (char **)malloc(sizeof(char *) * (main->export_len + 1));
	while (i < main->export_len)
	{
		sort_env[i] = ft_strdup(main->export[i]);
		i++;
	}
	i = 0;
	while (i < main->export_len - 1)
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
	while (i < main->export_len)
	{
		printf("%s\n", sort_env[i]);
		i++;
	}
	free_env(sort_env, main->export_len);
}

int	check_syntax_env(char **split)
{
	int	i;

	i = 1;
	if (ft_strcmp(split[0], "env") == 0 && split[1] == NULL)
		return (1);
	if (ft_strcmp(split[0], "env") == 0 && split[1] != NULL)
	{
		while (split[i])
		{
			if (ft_strcmp(split[i], "env") == 0)
				i++;
			else
				return (printf("env: ‘%s’: No such file or directory\n"
						, split[i]), 0);
		}
	}
	return (1);
}

int	print_env(t_main *main, int check, char **split)
{
	int	i;

	i = 0;
	if (check == 0)
	{
		if (check_syntax_env(split) == 0)
			return (1);
		while (i < main->env_len)
		{
			printf("%s\n", main->env[i]);
			i++;
		}
		printf("Env Len : %d | Export Len : %d\n", main->env_len, main->export_len);
	}
	if (check == 1)
	{
		print_ascii_order(main);
		printf("Export Len : %d\n", main->export_len);
	}
	return (0);
}

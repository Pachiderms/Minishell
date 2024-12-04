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

int	check_syntax_env(t_main *main, char **split)
{
	if (ft_strcmp(split[0], "env") == 0 && split[1] == NULL)
		return (1);
	if (ft_strcmp(split[0], "env") == 0 && split[1] != NULL)
	{
		int i = 1;
		while (i < main->split_len)
		{
			if (ft_strcmp(split[i], "env") == 0)
				i++;
			else
				return (printf("env: ‘%s’: No such file or directory\n", split[i]), 0);
		}
	}
	return (1);
}

void	print_env(t_main *main, int check, char **split)
{
	int	i;

	i = 0;
	if (check == 0)
	{
		if (check_syntax_env(main, split) == 0)
			return ;
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
	return ;
}
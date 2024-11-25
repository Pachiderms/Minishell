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

void	print_env(t_main *main, int check)
{
	int	i;

	i = 0;
	if (check == 0)
	{
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
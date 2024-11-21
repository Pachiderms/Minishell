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

void	print_env(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->env_len)
	{
		printf("%s\n", main->env[i]);
		i++;
	}
	printf("Env Len : %d\n", (main->env_len));
	return ;
}

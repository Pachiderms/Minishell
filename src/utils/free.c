/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:36:53 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/17 18:27:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_end_cmd(t_main *main, char **split)
{
	free_split(split);
	if (main->tokens)
		free_tokens(main);
}

void	free_split(char **split)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (split[len])
		len++;
	if (len <= 0)
		return ;
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_tokens(t_main *main)
{
	if (main->tokens)
		free(main->tokens);
	main->tokens = 0;
	main->tokens_len = 0;
}

void	free_all_data(t_main *main)
{
	if (main->env)
		free_env(main->env, main->env_len);
	if (main->export)
		free_env(main->export, main->export_len);
	free_tokens(main);
}

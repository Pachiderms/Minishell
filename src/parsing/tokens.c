/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:11 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_tokens(char **split, t_main *main)
{
	int		i;

	i = 0;
	if (!split)
		return (0);
	while (split[i] != NULL)
		i++;
	main->tokens_len = i;
	main->tokens = malloc(i * sizeof(t_token));
	if (!main->tokens)
		return (0);
	i = -1;
	while (split[++i] != NULL)
	{
		if (is_cmd(split[i], main->path))
			main->tokens[i].type = command;
		else if (is_sc(split[i]) > 0)
		{
			if (!handle_sc(main, split, i))
				return (0);
			if (!ft_strcmp(split[i], "<<"))
				main->hc_pos = i;
		}
		else
			main->tokens[i].type = argument;
		main->tokens[i].value = split[i];
	}
	// for(int i=0;split[i];i++)
	// 	printf("split : '%s' (token : %u)\n", split[i], main->tokens[i].type);
	main->nb_cmd = get_cmd_number(main, split);
	return (1);
}

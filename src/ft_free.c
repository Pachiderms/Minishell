/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:22:19 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/04 15:25:10 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_end_cmd(t_main *main, char **split)
{
    free_split(split);
    if (main->tokens)
        free(main->tokens);
    main->tokens = 0;
    main->tokens_len = 0;
}

void    free_split(char **split)
{
    int i;

    if (split)
    {
        i = 0;
        while (split[i])
            i++;
        while (i >= 0)
        {
            free(split[i]);
            i--;
        }
        free(split);
    }
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
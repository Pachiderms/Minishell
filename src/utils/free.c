/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:36:53 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/05 19:07:24 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_process(t_main *main, int exit_code)
{
	free_all_data(main);
	exit (exit_code);
}

void	free_end_cmd(t_main *main)
{
	ft_lstclear(&main->cmd_tokens);
	if (access("heredoc.tmp", F_OK) == 0)
		unlink("heredoc.tmp");
	main->u_token = NULL;
	if (main->last_ofile)
		free(main->last_ofile);
	main->last_ofile = NULL;
	main->nb_cmd = 0;
	free_split(main->cmdnf);
}

void	free_split(char **split)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (!split)
		return ;
	len = get_dchar_len(split);
	if (len <= 0)
		return ;
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

void	free_all_data(t_main *main)
{
	if (main->env)
		free_env(main->env, main->env_len);
	if (main->export)
		free_env(main->export, main->export_len);
	ft_lstclear(&main->cmd_tokens);
	main->u_token = NULL;
	if (main->last_ofile)
		free(main->last_ofile);
	free_split(main->cmdnf);
}

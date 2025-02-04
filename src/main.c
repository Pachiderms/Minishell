/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/04 00:30:51 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEFINE_I
#include "../includes/minishell.h"

int	only_space_line(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (i == (int)ft_strlen(cmd))
		return (free(cmd), 1);
	return (0);
}

////////////////////////////////////////////////////////////

void	sub_process(t_main *main, char *cmd)
{
	if (only_space_line(cmd) == 0 && cmd)
	{
		add_history(cmd);
		if (!order(cmd, main))
			ft_lstclear(&main->cmd_tokens);
		else
		{
			ft_process(main);
			free_end_cmd(main);
		}
		free(cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	static t_main	main;
	char			*cmd;
	static int		i;

	(void)argc;
	(void)argv;
	if (!init_main(&main, env))
		return (0);
	init_signals();
	while (1)
	{
		cmd = readline(GREEN"minishell> "RESET);
		if (cmd == NULL)
		{
			printf("exit\n");
			break ;
		}
		sub_process(&main, cmd);
		cat = 0;
		i++;
	}
	free_all_data(&main);
	rl_clear_history();
	return (0);
}

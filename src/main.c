/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/06 10:59:48 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_cat;

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
		if (check_var_exists(main->env, main->env_len, "export PATH=") != -1)
			main->current_path = main->env[check_var_exists(main->env,
					main->env_len, "export PATH=")];
		else
			main->current_path = NULL;
		add_history(cmd);
		if (!order(cmd, main))
		{
			if (main->u_token)
				main->last_exit_code = u_ttoken(main);
			free_end_cmd(main);
		}
		else
		{
			ft_process(main);
			free_end_cmd(main);
		}
		free(cmd);
		if (main->cmd_quotes)
			free(main->cmd_quotes);
		main->cmd_quotes = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	static t_main	main;
	char			*cmd;
	static int		i;

	(void)argc;
	(void)argv;
	g_cat = 0;
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
		g_cat = 0;
		i++;
	}
	free_all_data(&main);
	rl_clear_history();
	return (0);
}

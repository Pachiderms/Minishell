/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:12:38 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_data(t_main *main)
{
	if (main->env)
		free_old_env(main->env, main->env_len);
	/* if (main->tokens)
		// fonction à faire pour free une liste */
}

void	init_main(t_main *main)
{
	main->env = NULL;
	main->env_len = 0;
	main->tokens = NULL;
	main->tokens_len = 0;
	main->path = NULL;
}

int	init_env(char **env, t_main *main)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		continue ;
	main->env_len = i;
	main->env = (char **)malloc(sizeof(char *) * main->env_len + 1);
	if (!main->env)
		return (0);
	i = 0;
	while (i < main->env_len)
	{
		main->env[i] = ft_strdup(env[i]);
		i++;
	}
	return (1);
}

int	only_space_line(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (i == (int)ft_strlen(cmd))
		return (free(cmd), 1);
	return (0);
}

////////////////////////////////////////////////////////////

int	main(int argc, char **argv, char **env)
{
	t_main	main;
	char	*cmd;
	char	**split;
	char	**c_split;

	(void)argc;
	(void)argv;
	init_main(&main);
	if (init_env(env, &main) == 0)
		return (free_all_data(&main), 1);
	if (check_var_exists(&main, "export PATH=") != -1)
		main.path = env[check_var_exists(&main, "export PATH=")];
	else
		return (free_all_data(&main), 1);
	while (1)
	{
		cmd = readline(GREEN"minishell> "RESET);
		if (only_space_line(cmd) == 0 && cmd)
			add_history(cmd);
		split = ft_split(cmd, ' ');
		c_split = clean_split(split);
		if (init_tokens(c_split, &main) == 0)
			return (free_all_data(&main), 1);
		// partie exec à faire
		if (cmd[0] == 'e' && cmd[1] == 'n' && cmd[2] == 'v' && cmd[3] == '\0')
			print_env(&main);
		if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 'r' && cmd[5] == 't')
			update_env(&main, cmd, 1);
		if (cmd[0] == 'u' && cmd[1] == 'n' && cmd[2] == 's' && cmd[3] == 'e' && cmd[4] == 't')
			update_env(&main, cmd, 2);
		/* if (cmd[0] == 'c' && cmd[1] == 'd')
			update_env(&main, cmd, 3) */
	}
	free_all_data(&main);
	return (0);
}

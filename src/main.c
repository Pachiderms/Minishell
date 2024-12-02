/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2024/12/02 19:29:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *tokens, int tokens_len)
{
	int	i;

	i = tokens_len - 1;
	while (i >= 0)
	{
		free(tokens[i].value);
		i--;
	}
	return ;
}

void	free_all_data(t_main *main)
{
	if (main->env)
		free_env(main->env, main->env_len);
	if (main->export)
		free_env(main->export, main->export_len);
	/* if (main->tokens)
		free_tokens(main->tokens, main->tokens_len); */
}

void	init_main(t_main *main)
{
	main->env = NULL;
	main->env_len = 0;
	main->export = NULL;
	main->export_len = 0;
	main->tokens = NULL;
	main->tokens_len = 0;
	main->split_len = 0;
	main->nb_cmd = 0;
	main->path = NULL;
}

int	init_env(char **env, t_main *main)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		continue ;
	main->env_len = i;
	printf("Basic env len : %d\n", main->env_len);
	main->export_len = i - 1;
	printf("Basic export len : %d\n", main->export_len);
	main->env = (char **)malloc(sizeof(char *) * main->env_len + 1);
	main->export = (char **)malloc(sizeof(char *) * main->export_len + 1);
	if (!main->env || !main->export)
		return (0);
	i = 0;
	while (i < main->env_len)
	{
		main->env[i] = ft_strdup(env[i]);
		i++;
	}
	i = 0;
	while (i < main->export_len)
	{
		main->export[i] = ft_strdup(env[i]);
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
	static t_main	main;
	char	*cmd;
	char	**split;

	(void)argc;
	(void)argv;
	(void)cmd;
	init_main(&main);
	if (init_env(env, &main) == 0)
		return (free_all_data(&main), 1);
	if (check_var_exists(main.env, main.env_len, "export PATH=") != -1)
		main.path = env[check_var_exists(main.env, main.env_len, "export PATH=")];
	else
		return (free_all_data(&main), 1);
	while (1)
	{
		cmd = readline(GREEN"minishell> "RESET);
		if (only_space_line(cmd) == 0 && cmd)
		{
			add_history(cmd);
			split = ft_split_k_q_s(cmd, ' ');
			for(int i=0;split[i];i++)
				printf("split : %s\n", split[i]);
			// return (0);
			if (init_tokens(split, &main) == 0)
				return (free_all_data(&main), 1);
			ft_exec(&main, split, cmd);
			// ft_putendl_fd("end of while", 1);
		}
	}
	free_all_data(&main);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/03 14:19:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEFINE_I
#include "../includes/minishell.h"

void	set_null_main(t_main *main)
{
	main->env = NULL;
	main->env_len = 0;
	main->export = NULL;
	main->export_len = 0;
	main->nb_cmd = 0;
	main->path = NULL;
	main->cmd_tokens = NULL;
	main->u_token = NULL;

	// Dolalr struct //
	main->dollars.i = 0;
	main->dollars.j = 0;
	main->dollars.end = 0;
	main->dollars.r = 0;
	main->dollars.r1 = 0;
	main->dollars.rep_pos = 0;
	main->dollars.check = 0;
	main->dollars.arg_dup = NULL;
	main->dollars.tmp = NULL;
	main->dollars.tmp2 = NULL;
	main->dollars.tmp3 = NULL;
	main->dollars.final_tmp = NULL;
}

char	*get_var_name(char *cmd)
{
	int i;
	int j;
	char *var_name;

	i = 0;
	j = 0;
	if (ft_strncmp(cmd, "export ", 7) == 0)
		i = 7;
	while (cmd[i++] != '=')
		j++;
	var_name = (char *)malloc(sizeof(char) * (j + 2));
	i = 0;
	j = 0;
	if (ft_strncmp(cmd, "export ", 7) == 0)
		i = 7;
	while (cmd[i] != '=')
	{
		var_name[j] = cmd[i];
		j++;
		i++;
	}
	var_name[j] = cmd[i];
	var_name[j + 1] = '\0';
	return (var_name);
}

int	init_env(char **env, t_main *main)
{
	int	i;
	char *temp;

	i = -1;
	while (env[++i] != NULL)
		continue ;
	main->env_len = i;
	// printf("Basic env len : %d\n", main->env_len);
	main->export_len = i - 1;
	// printf("Basic export len : %d\n", main->export_len);
	main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1));
	main->export = (char **)malloc(sizeof(char *) * (main->export_len + 1));
	if (!main->env || !main->export)
		return (0);
	i = 0;
	while (i < main->env_len)
	{
		main->env[i] = ft_strdup(env[i]);
		i++;
	}
	main->env[i] = NULL;
	i = 0;
	while (i < main->export_len)
	{
		temp = ft_strjoin_free(ft_strjoin("\"", &ft_strchr(env[i], '=')[1]), "\"", 0);
		main->export[i] = ft_strjoin_free("export ", ft_strjoin_free(get_var_name(env[i]), temp, 0), 1);
		free(temp);
		i++;
	}
	main->export[i] = NULL;
	return (1);
}

int	init_main(t_main *main, char **env)
{
	set_null_main(main);
	if (init_env(env, main) == 0)
		return (free_all_data(main), 0);
	if (check_var_exists(main->env, main->env_len, "export PATH=") != -1)
		main->path = env[check_var_exists(main->env, main->env_len, "export PATH=")];
	else
		return (free_all_data(main), 0);
	return (1);
}

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

int	main(int argc, char **argv, char **env)
{
	static t_main	main;
	char	*cmd;
	static int i;

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
		if (only_space_line(cmd) == 0 && cmd)
		{
			add_history(cmd);
			if (!order(cmd, &main))
				ft_lstclear(&main.cmd_tokens);
			else
			{
				ft_process(&main);
				free_end_cmd(&main);
			}
		}
		free(cmd);
		cat = 0;
		i++;
	}
	free_all_data(&main);
	rl_clear_history();
	return (0);
}

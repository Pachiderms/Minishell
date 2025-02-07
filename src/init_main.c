/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/07 20:39:56 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_dollar(t_main *main)
{
	main->dollars_ok = 0;
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

void	set_null_main(t_main *main)
{
	main->env = NULL;
	main->env_len = 0;
	main->export = NULL;
	main->export_len = 0;
	main->nb_cmd = 0;
	main->path = NULL;
	main->current_path = NULL;
	main->cmd_tokens = NULL;
	main->u_token = NULL;
	main->last_ofile = NULL;
	main->cmd_quotes = NULL;
	main->last_exit_code = 0;
	main->nofile = NULL;
	main->lastcmd = -1;
	init_dollar(main);
	g_signal_pid = 0;
}

void	set_env(t_main *main, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < main->env_len)
	{
		main->env[i] = ft_strdup(env[i]);
		i++;
	}
	main->env[i] = NULL;
	i = 0;
	while (i < main->export_len)
	{
		tmp = ft_strjoin_free(
				ft_strjoin("\"", &ft_strchr(env[i], '=')[1]), "\"", 0);
		main->export[i] = ft_strjoin_free(
				"export ", ft_strjoin_free(get_var_name(env[i]), tmp, 0), 1);
		free(tmp);
		i++;
	}
	main->export[i] = NULL;
}

int	init_env(char **env, t_main *main)
{
	int		i;

	i = -1;
	while (env[++i] != NULL)
		continue ;
	main->env_len = i;
	main->export_len = i - 1;
	main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1));
	main->export = (char **)malloc(sizeof(char *) * (main->export_len + 1));
	if (!main->env || !main->export)
		return (0);
	set_env(main, env);
	return (1);
}

int	init_main(t_main *main, char **env)
{
	set_null_main(main);
	if (init_env(env, main) == 0)
		return (free_all_data(main), 0);
	if (check_var_exists(main->env, main->env_len, "export PATH=") != -1)
		main->path = env[check_var_exists(
				main->env, main->env_len, "export PATH=")];
	else
		return (free_all_data(main), 0);
	main->current_path = env[check_var_exists(
			main->env, main->env_len, "export PATH=")];
	return (1);
}

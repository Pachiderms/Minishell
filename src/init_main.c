/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/04 08:22:28 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	main->cmd_no_quotes = NULL;
	main->cmd_quotes = NULL;
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
	int		i;
	int		j;
	char	*var_name;

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
	main->current_path =  env[check_var_exists(
				main->env, main->env_len, "export PATH=")];
	return (1);
}

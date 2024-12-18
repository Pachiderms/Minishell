/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/19 16:33:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*get_var_name(char *cmd) // export aaa=aaa
{
	int i;
	int j;
	char *var_name;

	i = 0;
	j = 0;
	if (ft_strncmp(cmd, "export ", 7) == 0)
		i = 7;
	while (cmd[i] != '=')
	{
		j++;
		i++;
	}
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
	char *save_value;
	char *temp;

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
		save_value = ft_strjoin(ft_strjoin("\"", ft_strdup(&ft_strchr(env[i], '=')[1])), "\"");
		temp = save_value;
		save_value = ft_strjoin("export ", ft_strjoin(get_var_name(env[i]), temp));
		free(temp);
		main->export[i] = save_value;
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
			split = ft_split_k_q_s(&main, cmd, ' ');
			if (init_tokens(split, &main) == 0)
				return (free_all_data(&main), 1);
			for(int i=0;split[i];i++)
				printf("split : %s\n", split[i]);
			if (ft_exec(&main, split, cmd) == 0)
				return (free_all_data(&main), 1);
		}
	}
	free_all_data(&main);
	return (0);
}

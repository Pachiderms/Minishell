/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:04:53 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:04:55 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var_exists2(t_main *main, char *arg)
{
	int		i;
	int		j;
	char	*actual_var;

	i = 0;
	j = 0;
	if (ft_strcmp(arg, "?") == 0)
		return (-2);
	if (ft_strcmp(arg, "UID") == 0)
		return (-3);
	while (main->env[i])
	{
		actual_var = ft_strdup(main->env[i]);
		while (actual_var[j] != '=')
			j++;
		actual_var[j] = '\0';
		if (ft_strcmp(arg, actual_var) == 0)
			return (free(actual_var), i);
		free(actual_var);
		actual_var = NULL;
		j = 0;
		i++;
	}
	return (-1);
}

int	basic_verif(char *arg, int which)
{
	if (which == 0)
	{
		if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
			return (0);
		if (arg[0] == '\0' || arg[0] == '=' || ft_isdigit(arg[0]) == 1)
			return (ft_error("nvid", arg));
		if (arg[0] == '-' && arg[1])
			return (ft_error("io", &arg[1]));
	}
	if (which == 1)
	{
		if (arg[0] == '_' && arg[1] == '\0')
			return (0);
		if (arg[0] == '\0' || ft_isdigit(arg[0]) == 1)
			return (ft_error("nvid", arg));
		if (arg[0] == '-' && arg[1])
			return (ft_error("io", &arg[1]));
	}
	return (1);
}

int	check_syntax_unset(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	if (basic_verif(arg, 1) == 0)
		return (0);
	while (arg[i++])
	{
		if (arg[i] == '=' || arg[i] == '?' || arg[i] == '.' || arg[i] == '+'
			|| arg[i] == '{' || arg[i] == '}' || arg[i] == '-' || arg[i] == '*'
			|| arg[i] == '#' || arg[i] == '@' || arg[i] == '^' || arg[i] == '~')
			return (ft_error("nvid", arg));
	}
	i = 0;
	while (arg[i++])
	{
		if (arg[i] == '!')
			return (ft_error("evnf", ft_strchr(arg, '!')));
	}
	return (1);
}

void	unset(t_main *main, char *cmd)
{
	if (check_syntax_unset(cmd) == 0)
		return ;
	unset_env(main, cmd);
	unset_export(main, cmd);
	printf("Env Len : %d | Export Len : %d\n", main->env_len, main->export_len);
	return ;
}

int	prep_unset(t_main *main)
{
	char	*cmd;
	char	**to_unset;
	int		i;

	if (!main->cmd_tokens->args)
		return (print_env(main, 1), 0);
	to_unset = ft_split_k_q_s(main, main->cmd_quotes, ' ');
	i = 1;
	while (to_unset[i])
	{
		printf("split %s\n", to_unset[i]);
		cmd = ft_strjoin("export ", to_unset[i]);
		unset(main, cmd);
		free(cmd);
		i++;
	}
	return (free_split(to_unset), 0);
}

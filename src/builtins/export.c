/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:08:43 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:08:45 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remake_env_fill(char **tmp, t_main *main, int which)
{
	int	i;

	i = 0;
	if (which == 0)
	{
		while (i < main->env_len)
		{
			tmp[i] = ft_strdup(main->env[i]);
			i++;
		}
	}
	if (which == 1)
	{
		while (i < main->export_len)
		{
			tmp[i] = ft_strdup(main->export[i]);
			i++;
		}
	}
}

int	check_ko_export(char *arg)
{
	int	i;

	i = 0;
	if (basic_verif(arg, 0) == 0)
		return (0);
	while (arg[i++])
	{
		if (arg[i] == '!' && arg[i + 1] != '=')
			return (ft_error("evnf", ft_strchr(arg, '!')));
	}
	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '%' || arg[i] == '?' || arg[i] == '@'
			|| arg[i] == '\\' || arg[i] == '~' || arg[i] == '-'
			|| arg[i] == '.' || arg[i] == '}' || arg[i] == '{'
			|| arg[i] == '*' || arg[i] == '#'
			|| (arg[i] == '+' && arg[i + 1] != '=')
			|| arg[i] == ' ' || arg[i] == '!')
			return (ft_error_export("nvid", arg));
		i++;
	}
	return (1);
}

int	check_syntax_export(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	if (!cmd)
		return (0);
	arg = &ft_strchr(cmd, ' ')[1];
	if (check_ko_export(arg) == 0)
		return (0);
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg[i] == '=')
		return (1);
	else
		return (2);
	return (2);
}

int	export(t_main *main, char *cmd)
{
	int		syntax;
	int		plus;
	char	*plus_str;

	syntax = check_syntax_export(cmd);
	if (syntax == 0)
		return (1);
	else if (syntax == 1)
	{
		plus = check_plus(cmd);
		if (plus == 1)
		{
			plus_str = get_plus_str(main, cmd);
			fill_env_export(main, plus_str);
		}
		else
			fill_env_export(main, cmd);
	}
	else if (syntax == 2)
	{
		fill_export(main, cmd);
	}
	return (0);
}

int	prep_export(t_main *main, t_cmd *token)
{
	char	*cmd;
	char	**to_export;
	int		i;
	int		exit_code;

	exit_code = 0;
	if (!main->cmd_tokens->args)
		return (print_env(main, 1, token), 0);
	to_export = ft_split_k_q_s(main, main->cmd_quotes, ' ', 1);
	i = 1;
	while (to_export[i])
	{
		cmd = ft_strjoin("export ", to_export[i]);
		if (export(main, cmd) == 1)
			exit_code = 1;
		free(cmd);
		i++;
	}
	return (free_split(to_export), exit_code);
}

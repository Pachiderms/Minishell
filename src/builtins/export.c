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
			return (printf("minishell: %s: event not found\n", ft_strchr(arg, '!'))
				, 0);
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
			return (printf("minishell: export: ‘%s’: not a valid identifier\n", arg)
				, 0);
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

void	export(t_main *main, char *cmd)
{
	int		syntax;
	int		plus;
	char	*plus_str;

	syntax = check_syntax_export(cmd);
	if (syntax == 0)
		return ;
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
		printf("Env Len : %d | Export Len : %d\n", main->env_len, main->export_len);
	}
	else if (syntax == 2)
	{
		fill_export(main, cmd);
		printf("Export Len : %d\n", main->export_len);
	}
	return ;
}

int	prep_export(t_main *main)
{
	char	*cmd;

	cmd = main->cmd_tokens->args;
	if (!check_syntax_export(cmd))
		return (0);
	if (get_arg_len(&ft_strchr(main->cmd_tokens->args, '=')[1]) > 1)
		cmd = cut_str(cmd, ft_strrchr(cmd, ' '));
	cmd = ft_strjoin("export ", cmd);
	export(main, cmd);
	free(cmd);
	return (0);
}

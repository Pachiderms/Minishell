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

int	check_ko_export(char *arg) // trop de lignes
{
	int	i;

	i = 0;
	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return (0);
	if (arg[0] == '\0' || arg[0] == '=' || ft_isdigit(arg[0]) == 1)
		return (printf("bash: export: ‘%s’: not a valid identifier\n", arg), 0);
	if (arg[0] == '-' && arg[1])
		return (printf("bash: export: -%c: invalid option\n", arg[1]), 0);
	while (arg[i++])
	{
		if (arg[i] == '!' && arg[i + 1] != '=')
			return (printf("bash: %s: event not found\n", ft_strchr(arg, '!'))
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
			return (printf("bash: export: ‘%s’: not a valid identifier\n", arg)
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

int	prep_export(t_main *main, char **split)
{
	int		i;
	char	*tmp;

	i = 1;
	if (ft_strcmp(split[0], "export") == 0 && split[1] == NULL)
	{
		print_env(main, 1, split);
		return (0);
	}
	while (split[i] && is_sc(split[i]) != 1)
	{
		printf("split : '%s'\n", split[i]);
		tmp = ft_strjoin("export ", split[i]);
		export(main, tmp);
		free(tmp);
		i++;
	}
	return (0);
}

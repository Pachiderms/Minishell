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

void	fill_env_export(t_main *main, char *cmd)
{
	int		i;
	int		replace_pos;
	char	**tmp;

	i = 0;
	replace_pos = check_var_exists(main->env, main->env_len, cmd);
	tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
	while (i < main->env_len)
	{
		tmp[i] = ft_strdup(main->env[i]);
		i++;
	}
	free_env(main->env, main->env_len);
	if (replace_pos >= 0)
		main->env = (char **)malloc(sizeof(char *) * ((main->env_len) + 1));
	else
		main->env = (char **)malloc(sizeof(char *) * ((main->env_len + 1) + 1));
	i = 0;
	while (i < main->env_len)
	{
		if (i == replace_pos)
		{
			main->env[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			i++;
		}
		main->env[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			main->env[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			i++;
		}
	}
	main->env[i] = NULL;
	free_env(tmp, main->env_len);
	if (replace_pos == -1)
	{
		main->env[i] = main->env[i - 1];
		main->env[i - 1] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
		main->env_len += 1;
	}
	fill_export(main, cmd);
}

void	fill_export(t_main *main, char *cmd)
{
	int		i;
	int		replace_pos;
	char	**tmp;
	char *save_value;
	char *temp;

	i = 0;
	replace_pos = check_var_exists(main->export, main->export_len, cmd);
	printf("replace_pos : %d\n", replace_pos);
	tmp = (char **)malloc(sizeof(char *) * main->export_len + 1);
	while (i < main->export_len)
	{
		tmp[i] = ft_strdup(main->export[i]);
		i++;
	}
	free_env(main->export, main->export_len);
	if (replace_pos >= 0)
		main->export = (char **)malloc(sizeof(char *) * ((main->export_len) + 1));
	else
		main->export = (char **)malloc(sizeof(char *) * ((main->export_len + 1) + 1));
	i = 0;
	while (i < main->export_len)
	{
		if (i == replace_pos)
		{
			if (ft_strchr(cmd, '='))
			{
				save_value = ft_strjoin(ft_strjoin("\"", &ft_strchr(cmd, '=')[1]), "\"");
				temp = save_value;
				save_value = ft_strjoin("export ", ft_strjoin(get_var_name(cmd), temp));
				free(temp);
				main->export[i] = save_value;
			}
			else
				main->export[i] = ft_strjoin("export ", &ft_strchr(cmd, ' ')[1]);
			i++;
		}
		main->export[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			if (ft_strchr(cmd, '='))
			{
				save_value = ft_strjoin(ft_strjoin("\"", &ft_strchr(cmd, '=')[1]), "\"");
				temp = save_value;
				save_value = ft_strjoin("export ", ft_strjoin(get_var_name(cmd), temp));
				free(temp);
				main->export[i] = save_value;
			}
			else
				main->export[i] = ft_strjoin("export ", &ft_strchr(cmd, ' ')[1]);
			i++;
		}
	}
	main->export[i] = NULL;
	free_env(tmp, main->export_len);
	if (replace_pos == -1)
	{
		main->export[i] = main->export[i - 1];
		if (ft_strchr(cmd, '='))
		{
			save_value = ft_strjoin(ft_strjoin("\"", &ft_strchr(cmd, '=')[1]), "\"");
			temp = save_value;
			save_value = ft_strjoin("export ", ft_strjoin(get_var_name(cmd), temp));
			free(temp);
			main->export[i - 1] = save_value;
		}
		else
			main->export[i - 1] = ft_strjoin("export ", &ft_strchr(cmd, ' ')[1]);
		main->export_len += 1;
	}
}

int	check_syntax_export(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return (0);
	if (arg[0] == '\0' || arg[0] == '=' || ft_isdigit(arg[0]) == 1)
		return (printf("bash: export: ‘%s’: not a valid identifier\n", arg), 0);
	if (arg[0] == '-' && arg[1])
		return (printf("bash: export: -%c: invalid option\n", arg[1]), 0);
	while (arg[i])
	{
		if (arg[i] == '!' && arg[i + 1] != '=')
			return (printf("bash: %s: event not found\n", ft_strchr(arg, '!')), 0);
		else if (arg[i] == '!')
			return (printf("bash: export: ‘%s’: not a valid identifier\n", arg), 0);
		i++;
	}
	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '%' || arg[i] == '?' || arg[i] == '@'
			|| arg[i] == '\\' || arg[i] == '~' || arg[i] == '-'
			|| arg[i] == '.' || arg[i] == '}' || arg[i] == '{'
			|| arg[i] == '*' || arg[i] == '#'
			|| (arg[i] == '+' && arg[i + 1] != '='))
			return (printf("bash: export: ‘%s’: not a valid identifier\n", arg), 0);
		i++;																																		
	}
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (arg[i - 1] == ' ' || i == 0 || arg[i] == '\0')
				return (printf("HERE0"), 0);
			else
				return (1); // 1 pour mettre dans env et export
		}
		i++;
	}
	if (i == 0)
		return (printf("HERE"), 0);
	/* if (arg[i - 1] == ' ')
		return (printf("HERE2"), free(arg), 0); */
	return (2); // 2 pour mettre seulement dans export
}

int check_plus(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	while (arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		return (1);
	return (0);
}

char	*get_without_plus(char *cmd)
{
	int		i;
	int		j;
	char	*arg;
	char	*str;

	i = 0;
	j = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	str = (char *)malloc(sizeof(char) * ft_strlen(arg));
	while (arg[i])
	{
		if (arg[i] != '+')
		{
			str[j] = arg[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_plus_str(t_main *main, char *cmd)
{
	int	replace_pos;
	char	*arg;

	replace_pos = check_var_exists(main->env, main->env_len, cmd);
	if (replace_pos == -1)
		arg = ft_strjoin("export ", get_without_plus(cmd));
	else
		arg = ft_strjoin(ft_strjoin("export ", main->env[replace_pos]), &ft_strchr(cmd, '=')[1]);
	return (arg);
}

void	export(t_main *main, char *cmd)
{
	int	syntax;
	int plus;
	char *plus_str;

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
	int i;
	char *tmp;

	i = 1;
	if (ft_strcmp(split[0], "export") == 0 && split[1] == NULL)
	{
		print_env(main, 1, split);
		return (0);
	}
	while (split[i] && is_sc(split[i]) != 1)
	{
		printf("split : '%s'\n", split[i]); //
		tmp = ft_strjoin("export ", split[i]);
		export(main, tmp);
		free(tmp);
		i++;
	}
	return (0);
}

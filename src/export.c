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

void	print_ascii_order(t_main *main)
{
	int		i;
	char	*tmp;
	char	**sort_env;

	i = 0;
	sort_env = (char **)malloc(sizeof(char *) * main->export_len + 1);
	while (i < main->export_len)
	{
		sort_env[i] = ft_strdup(main->export[i]);
		i++;
	}
	i = 0;
	while (i < main->export_len - 1)
	{
		if (ft_strncmp(sort_env[i], sort_env[i + 1], -1) > 0)
		{
			tmp = sort_env[i + 1];
			sort_env[i + 1] = sort_env[i];
			sort_env[i] = tmp;
			i = 0;
		}
		i++;
	}
	tmp = sort_env[1];
	sort_env[1] = sort_env[0];
	sort_env[0] = tmp;
	i = 0;
	while (i < main->export_len)
	{
		printf("%s\n", sort_env[i]);
		i++;
	}
	free_env(sort_env, main->export_len);
}

void	prep_export(t_main *main, char **split)
{
	int i;
	char *tmp;

	i = 1;
	if (ft_strcmp(split[0], "export") == 0 && split[1] == NULL)
	{
		print_env(main, 1, split);
		return ;
	}
	while (split[i] && is_sc(split[i]) != 1)
	{
		tmp = ft_strjoin("export ", split[i]);
		export(main, tmp);
		free(tmp);
		i++;
	}
}

int	check_syntax_export(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return (free(arg), 0);
	if (ft_isdigit(arg[0]) == 1 || arg[0] == '=')
		return (printf("bash: export: '%c': not a valid identifier\n", arg[0]), free(arg), 0);
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '%' || arg[i] == '?' || arg[i] == '@'
			|| arg[i] == '\\' || arg[i] == '~' || arg[i] == '-'
			|| arg[i] == '.' || arg[i] == '}' || arg[i] == '{'
			|| arg[i] == '*' || arg[i] == '#' || arg[i] == '!'
			|| (arg[i] == '+' && arg[i + 1] != '='))
			return (printf("bash: export: '%c': not a valid identifier\n", arg[i]), free(arg), 0);
		i++;																																		
	}
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (arg[i - 1] == ' ' || i == 0 || arg[i] == '\0')
				return (free(arg), 0);
			else
				return (1); // 1 pour mettre dans env et export
		}
		i++;
	}
	if (i == 0)
		return (free(arg), 0);
	if (arg[i - 1] == ' ')
		return (free(arg), 0);
	free(arg);
	return (2); // 2 pour mettre seulement dans export
}



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
		main->env = (char **)malloc(sizeof(char *) * (main->env_len) + 1);
	else
		main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1) + 1);
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

	i = 0;
	replace_pos = check_var_exists(main->export, main->export_len, cmd);
	tmp = (char **)malloc(sizeof(char *) * main->export_len + 1);
	while (i < main->export_len)
	{
		tmp[i] = ft_strdup(main->export[i]);
		i++;
	}
	free_env(main->export, main->export_len);
	if (replace_pos >= 0)
		main->export = (char **)malloc(sizeof(char *) * (main->export_len) + 1);
	else
		main->export = (char **)malloc(sizeof(char *) * (main->export_len + 1) + 1);
	i = 0;
	while (i < main->export_len)
	{
		if (i == replace_pos)
		{
			main->export[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			i++;
		}
		main->export[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			main->export[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			i++;
		}
	}
	free_env(tmp, main->export_len);
	if (replace_pos == -1)
	{
		main->export[i] = main->export[i - 1];
		main->export[i - 1] = ft_strdup(ft_strjoin(&ft_strchr(cmd, ' ')[1], "="));
		main->export_len += 1;
	}
}

int check_plus(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
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
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
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
	return (free(arg), str);
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
	printf("Syntax : %d\n", syntax);
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



/* #include "../includes/minishell.h"

void	print_ascii_order(t_main *main)
{
	int		i;
	char	*tmp;
	char	**sort_env;

	i = 0;
	sort_env = (char **)malloc(sizeof(char *) * main->export_len + 1);
	while (i < main->export_len)
	{
		sort_env[i] = ft_strdup(main->export[i]);
		i++;
	}
	i = 0;
	while (i < main->export_len - 1)
	{
		if (ft_strncmp(sort_env[i], sort_env[i + 1], -1) > 0)
		{
			tmp = sort_env[i + 1];
			sort_env[i + 1] = sort_env[i];
			sort_env[i] = tmp;
			i = 0;
		}
		i++;
	}
	tmp = sort_env[1];
	sort_env[1] = sort_env[0];
	sort_env[0] = tmp;
	i = 0;
	while (i < main->export_len)
	{
		printf("%s\n", sort_env[i]);
		i++;
	}
	free_env(sort_env, main->export_len);
}

void	prep_export(t_main *main, char **split)
{
	int i;
	char *tmp;

	i = 1;
	if (ft_strcmp(split[0], "export") == 0 && split[1] == NULL)
	{
		print_env(main, 1);
		return ;
	}
	while (split[i] && is_sc(split[i]) != 1)
	{
		tmp = ft_strjoin("export ", split[i]);
		export(main, tmp);
		free(tmp);
		i++;
	}
}

int	check_syntax_export(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	if (arg[0] == '_' && (arg[1] == '=' || arg[1] == '\0'))
		return (free(arg), 0);
	if (ft_isdigit(arg[0]) == 1 || arg[0] == '=')
		return (printf("bash: export: '%c': not a valid identifier\n", arg[0]), free(arg), 0);
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '%' || arg[i] == '?' || arg[i] == '@'
			|| arg[i] == '\\' || arg[i] == '~' || arg[i] == '-'
			|| arg[i] == '.' || arg[i] == '}' || arg[i] == '{'
			|| arg[i] == '*' || arg[i] == '#' || arg[i] == '!'
			|| (arg[i] == '+' && arg[i + 1] != '='))
			return (printf("bash: export: '%c': not a valid identifier\n", arg[i]), free(arg), 0);
		i++;																																		
	}
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (arg[i - 1] == ' ' || i == 0 || arg[i] == '\0')
				return (free(arg), 0);
			else
				return (1); // 1 pour mettre dans env et export
		}
		i++;
	}
	if (i == 0)
		return (free(arg), 0);
	if (arg[i - 1] == ' ')
		return (free(arg), 0);
	free(arg);
	return (2); // 2 pour mettre seulement dans export
}

char	*get_without_plus(char *cmd)
{
	int		i;
	int		j;
	char	*arg;
	char	*str;

	i = 0;
	j = 0;
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
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
	return (free(arg), str);
}

void	fill_env_export(t_main *main, char *cmd, int plus)
{
	int		i;
	int		replace_pos;
	char	*arg;
	char	**tmp;

	i = 0;
	replace_pos = check_var_exists(main->env, main->env_len, cmd);
	if (plus == 1)
		arg = get_without_plus(cmd);
	else
		arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
	while (i < main->env_len)
	{
		tmp[i] = ft_strdup(main->env[i]);
		i++;
	}
	free_env(main->env, main->env_len);
	if (replace_pos >= 0)
		main->env = (char **)malloc(sizeof(char *) * (main->env_len) + 1);
	else
		main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1) + 1);
	i = 0;
	while (i < main->env_len)
	{
		if (i == replace_pos)
		{
			if (plus == 0)
				main->env[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			else
				main->env[i] = ft_strjoin(main->env[i], ft_strdup(arg));
			i++;
		}
		main->env[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			if (plus == 0)
				main->env[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			else
				main->env[i] = ft_strjoin(main->env[i], ft_strdup(arg));
			i++;
		}
	}
	free_env(tmp, main->env_len);
	if (replace_pos == -1)
	{
		main->env[i] = main->env[i - 1];
		main->env[i - 1] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
		main->env_len += 1;
	}
	free(arg);
	fill_export(main, cmd, plus);
}

void	fill_export(t_main *main, char *cmd, int plus)
{
	int		i;
	int		replace_pos;
	char	*arg;
	char	**tmp;

	i = 0;
	replace_pos = check_var_exists(main->export, main->export_len, cmd);
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	tmp = (char **)malloc(sizeof(char *) * main->export_len + 1);
	while (i < main->export_len)
	{
		tmp[i] = ft_strdup(main->export[i]);
		i++;
	}
	free_env(main->export, main->export_len);
	if (replace_pos >= 0)
		main->export = (char **)malloc(sizeof(char *) * (main->export_len) + 1);
	else
		main->export = (char **)malloc(sizeof(char *) * (main->export_len + 1) + 1);
	i = 0;
	while (i < main->export_len)
	{
		if (i == replace_pos)
		{
			if (plus == 0)
				main->export[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			else
				main->export[i] = ft_strjoin(&ft_strchr(main->export[i], '=')[1], ft_strdup(&ft_strchr(cmd, ' ')[1]));
			i++;
		}
		main->export[i] = ft_strdup(tmp[i]);
		i++;
		if (i == replace_pos)
		{
			if (plus == 0)
				main->export[i] = ft_strdup(&ft_strchr(cmd, ' ')[1]);
			else
				main->export[i] = ft_strjoin(&ft_strchr(main->export[i], '=')[1], ft_strdup(&ft_strchr(cmd, ' ')[1]));
			i++;
		}
	}
	free_env(tmp, main->export_len);
	if (replace_pos == -1)
	{
		main->export[i] = main->export[i - 1];
		main->export[i - 1] = ft_strdup(ft_strjoin(&ft_strchr(cmd, ' ')[1], "="));
		main->export_len += 1;
	}
	free(arg);
}

int check_plus(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = ft_strdup(&ft_strchr(cmd, ' ')[1]);
	while (arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		return (1);
	return (0);
}

void	export(t_main *main, char *cmd)
{
	int	syntax;
	int plus;

	syntax = check_syntax_export(cmd);
	printf("Syntax : %d\n", syntax);
	if (syntax == 0)
		return ;
	else if (syntax == 1)
	{
		plus = check_plus(cmd);
		printf("plus : %d\n", plus);
		fill_env_export(main, cmd, plus);
		printf("Env Len : %d | Export Len : %d\n", main->env_len, main->export_len);
	}
	else if (syntax == 2)
	{
		fill_export(main, cmd, 0);
		printf("Export Len : %d\n", main->export_len);
	}
	return ;
} */
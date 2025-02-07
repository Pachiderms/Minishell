/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:07:16 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 14:36:52 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *_s)
{
	char	*s;

	if (!_s)
		return (0);
	s = get_cmd(_s);
	if (!ft_strncmp(s, "echo", -1) || (!ft_strncmp(s, "cd", -1)
			|| !ft_strncmp(s, "/bin/cd", -1))
		|| !ft_strncmp(s, "pwd", -1) || !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1)
		|| (!ft_strncmp(s, "env", -1) || !ft_strncmp(s, "/bin/env", -1))
		|| !ft_strncmp(s, "exit", -1))
		return (1);
	return (0);
}

int	check_first_cmd(char *s, t_main *main)
{
	int	dir;
	int	check;
	int	check2;

	dir = chdir(s);
	check = (dir == 0);
	check2 = 0;
	if (dir == 0)
		return_to_pwd(main);
	if (!ft_strcmp(s, "\0") || !ft_strcmp(s, ".."))
		check2 = 0;
	if (!ft_strncmp(&s[0], "./", 2)
		&& access(&ft_strchr(s, '/')[1], F_OK) == 0)
		check2 = 1;
	if (!ft_strncmp(&s[0], "./", 2)
		&& access(&ft_strchr(s, '/')[1], X_OK) == -1)
	{
		main->noFile = ft_strdup(s);
		check2 = -1;
	}
	if (!check && check2 == -1)
		return (0);
	if (check && check2)
		return (0);
	if (check && !check2)
		return (0);
	if (!check && check2)
		return (1);
	return (-1);
}

int	is_cmd(char *s, t_main *main)
{
	int		i;
	char	*s1;
	char	*tmp;
	char	**split;

	i = -1;
	tmp = NULL;
	if (!s)
		return (0);
	if (check_first_cmd(s, main) == 1)
		return (1);
	if (check_first_cmd(s, main) == 0)
		return (0);
	s1 = ft_strjoin("/", get_cmd(s));
	split = ft_split(main->path, ':');
	if (check_builtin(s))
		return (free_split(split), free(s1), 1);
	while (split[++i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, F_OK) == 0)
			return (free(tmp), free_split(split), free(s1), 1);
		free(tmp);
	}
	return (free_split(split), free(s1), 0);
}

int	is_sc(char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "|") == 0 || ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, ">>") == 0)
		return (1);
	if (ft_strchr(s, '$'))
		return (2);
	return (0);
}

int	check_global_syntax(char *arg, t_main *main)
{
	int	i;
	int	j;

	i = 0;
	if (!arg)
		return (1);
	while (i < (int)ft_strlen(arg))
	{
		i += was_in_quotes(&arg[i], main, ft_substr(&arg[i], 0, ft_strlen(&arg[i])));
		if (i > (int)ft_strlen(arg))
			break ;
		if (ft_strncmp(&arg[i], "<<", 2) == 0
			|| ft_strncmp(&arg[i], ">>", 2) == 0
			|| ft_strncmp(&arg[i], "<>", 2) == 0)
		{
			j = i + skip_char(&arg[i + 2], ' ', 0) + 2;
			if (i != j)
			{
				if (ft_strncmp(&arg[j], "<<", 2) == 0)
					main->u_token = "<<";
				else if (ft_strncmp(&arg[j], ">>", 2) == 0)
					main->u_token = ">>";
				else if (ft_strncmp(&arg[j], "<>", 2) == 0)
					main->u_token = "<>";
				else if (ft_strncmp(&arg[j], "><", 2) == 0)
					main->u_token = "><";
				else if (ft_strncmp(&arg[j], "<", 1) == 0)
					main->u_token = "<";
				else if (ft_strncmp(&arg[j], ">", 1) == 0)
					main->u_token = ">";
			}
			if (arg[i + 2] == '\0')
				main->u_token = "newline";
			else if (arg[i + 2] == arg[i])
			{
				if (arg[i] == '>')
					main->u_token = ">>";
				else if (arg[i] == '<')
					main->u_token = "<<";
			}
		}
		else if (ft_strncmp(&arg[i], "<", 1) == 0
			|| ft_strncmp(&arg[i], ">", 1) == 0)
		{
			j = i + skip_char(&arg[i + 1], ' ', 0) + 1;
			if (i != j)
			{
				if (ft_strncmp(&arg[j], "<<", 2) == 0)
					main->u_token = "<<";
				else if (ft_strncmp(&arg[j], ">>", 2) == 0)
					main->u_token = ">>";
				else if (ft_strncmp(&arg[j], "<>", 2) == 0)
					main->u_token = "<>";
				else if (ft_strncmp(&arg[j], "><", 2) == 0)
					main->u_token = "><";
				else if (ft_strncmp(&arg[j], "<", 1) == 0)
					main->u_token = "<";
				else if (ft_strncmp(&arg[j], ">", 1) == 0)
					main->u_token = ">";
			}
			if (arg[i + 1] == '\0')
				main->u_token = "newline";
		}
		if (main->u_token)
			break ;
		i++;
	}
	return (main->u_token == NULL);
}

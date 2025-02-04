/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:07:16 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 06:39:39 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *_s)
{
	char	*s;

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

int	is_cmd(char *s, char *path)
{
	int		i;
	char	*s1;
	char	*tmp;
	char	**split;

	i = 0;
	tmp = NULL;
	if (!ft_strcmp(s, "\0") || !ft_strcmp(s, ".."))
		return (0);
	if (!ft_strncmp(&s[0], "./", 2))
		return (1);
	if (ft_strchr(s, '/'))
		return (0);
	s1 = ft_strjoin("/", get_cmd(s));
	split = ft_split(path, ':');
	if (check_builtin(s))
		return (free_split(split), free(s1), 1);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, F_OK) == 0)
			return (free(tmp), free_split(split), free(s1), 1);
		free(tmp);
		i++;
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
	int j;

	i = 0;
	while (arg[i])
	{
		if (ft_strncmp(&arg[i], "<<", 2) == 0
			|| ft_strncmp(&arg[i], ">>", 2) == 0
			|| ft_strncmp(&arg[i], "<>", 2) == 0)
		{
			j = i + skip_char(&arg[i + 2], ' ', 0) + 2;
			printf("arg la i %d j %d %s\n", i , j, &arg[j]);
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
			printf("arg la i %d j %d %s\n", i , j, &arg[j]);
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
	printf("u token %s\n", main->u_token);
	return (main->u_token == NULL);
}

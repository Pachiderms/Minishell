/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/01/31 15:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *_s)
{
	char	*s;

	s = get_cmd(_s);
	if (!ft_strncmp(s, "echo", -1) || (!ft_strncmp(s, "cd", -1)  || !ft_strncmp(s, "/bin/cd", -1))
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

int	closed_quotes1(char const *s, int *i, int *_qts, char q)
{
	if (*_qts == 1)
	{
		while (s[*i] != q && s[*i])
			*i += 1;
		if (s[*i] == q)
		{
			*_qts = 0;
			*i += 1;
			return (1);
		}
	}
	return (0);
}

int	check_open_quotes(char const *s, t_main *main)
{
	int i;
	int s_qts;
	int d_qts;
	int tmp;

	i = 0;
	s_qts = 0;
	d_qts = 0;
	tmp = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (s[i] == '\'')
				s_qts = 1;
			else if (s[i] == '"')
				d_qts = 1;
			tmp = i;
			i++;
		}
		if (closed_quotes1(s, &i, &s_qts, '\'') == 1)
			main->s_qs[main->dollars.r++] = tmp;
		else if (closed_quotes1(s, &i, &d_qts, '"') == 1)
			main->d_qs[main->dollars.r1++] = tmp;
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	main->s_qs[main->dollars.r++] = -1;
	main->d_qs[main->dollars.r1++] = -1;
	main->dollars.r = 0;
	main->dollars.r1 = 0;
	//printf("s_qts : %d | d_qts : %d\n", s_qts, d_qts);
	if (s_qts == 1 || d_qts == 1)
		return (0);
	return (1);
}

int check_syntax_redirect(char *s, t_main *main)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], ">>", 2) || !ft_strncmp(&s[i], "<<", 2)
			|| !ft_strncmp(&s[i], "<>", 2))
		{
			j = i + 2;
			while (ft_isspace(s[j]))
				j++;
			if (s[j] == '\0')
				main->u_token = "newline";
		}
		else if (!ft_strncmp(&s[i], ">", 1) || !ft_strncmp(&s[i], "<", 1))
		{
			j = i + 1;
			while (ft_isspace(s[j]))
				j++;
			if (s[j] == '\0')
				main->u_token = "newline";
		}
		i++;	
	}
	printf("u_token : %s\n", main->u_token);
	return (!main->u_token);
}

char	*handle_sc_c(char *arg, t_main *main)
{
	char *arg_without_quotes;

	arg_without_quotes = NULL;
	if (arg == NULL)
		return (NULL);
	// if (check_syntax_redirect(arg, main) == 0)
	// 	return (NULL);
	if (main->s_qs[0] == -1 || main->d_qs[0] == -1)
	{
		if (ft_strcmp(arg, "!") == 0 || ft_strcmp(arg, ":") == 0)
			return (free(arg), ft_strdup(""));
	}
	if (main->s_qs[0] > -1 || main->d_qs[0] > -1)
	{
		arg_without_quotes = get_rid_of_quotes(ft_strdup(arg));
		if (ft_strcmp(arg_without_quotes, ":") == 0)
			return (free(arg_without_quotes), ft_strdup(""));
	}
	return (arg);
}



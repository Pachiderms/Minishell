/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "echo", -1) || (!ft_strncmp(s, "cd", -1))
		|| !ft_strncmp(s, "pwd", -1) || !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1) || (!ft_strncmp(s, "env", -1)
			|| !ft_strncmp(s, "/bin/env", -1))
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
	if (!ft_strncmp(s, "./", 2))
		return (1);
	s1 = ft_strjoin("/", s);
	split = ft_split(path, ':');
	if (check_builtin(s))
		return (free(split), free(s1), 1);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, R_OK) == 0)
		{
			return (free(tmp), free(split), free(s1), 1);
		}
		tmp = NULL;
		free(tmp);
		i++;
	}
	return (free(split), free(s1), 0);
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

char	*replace_dollar(char *s, t_main *main)
{
	int		i;
	int		j;
	int		l;
	char	*res;
	char	*tmp;

	i = 0;
	res = 0;
	while (s[i])
	{
		j = i;
		while (s[j] && s[j] != '$')
			j++;
		if (j != i)
		{
			tmp = ft_substr(s, i, j - i);
			res = ft_strjoin_free(res, tmp);
			free(tmp);
			tmp = NULL;
		}
		if (s[i + 1] && (s[i + 1] == '$' || s[i + 1] == '?'))
			return (ft_strdup(s));
		i = j;
		if (s[i] == '$')
		{
			while (s[j] && s[j] != '=')
				j++;
			tmp = ft_substr(s, i, j - i);
			l = check_var_exists2(main, &tmp[1]);
			if (l >= 0)
				res = ft_strjoin_free(res, &ft_strchr(main->env[l], '=')[1]);
			free(tmp);
			tmp = NULL;
			i = j;
		}
	}
	printf("final res: %s\n", res);
	return (res);
}

int	handle_sc(t_main *main, char **split, int i)
{
	int		sc_type;

	sc_type = is_sc(split[i]);
	if (sc_type == 1)
	{
		main->tokens[i].type = sc;
		return (1);
	}
	if (sc_type == 2)
	{
		split[i] = replace_dollar(split[i], main);
		main->tokens[i].type = argument;
		return (1);
	}
	return (0);
}

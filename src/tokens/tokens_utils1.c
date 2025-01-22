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

char	*get_rid_of_quotes(char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			len++;
	}
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			dest[len++] = s[i];
	}
	dest[len++] = '\0';
	return (free(s), dest);
}

char	*get_rid_of(char *s, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			len++;
	}
	tmp = malloc(len * sizeof(char) + 1);
	if (!tmp)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			tmp[len++] = s[i];
	}
	tmp[len++] = '\0';
	return (tmp);
}

int	check_builtin(char *s)
{
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
	if (!ft_strncmp(s, "./", 2))
		return (1);
	s1 = ft_strjoin("/", s);
	split = ft_split(path, ':');
	if (check_builtin(s))
		return (free_split(split), free(s1), 1);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, R_OK) == 0)
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

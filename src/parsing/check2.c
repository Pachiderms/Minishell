/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:07:16 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 00:08:00 by tzizi            ###   ########.fr       */
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

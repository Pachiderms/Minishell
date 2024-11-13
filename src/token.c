/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:14:34 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/13 14:29:40 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

int	ft_findmltpchar(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd") || !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset") || !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

int	is_cmd(char *s, char *path)
{
	int		i;
	char	*s1;
	char	**split;

	i = 0;
	s1 = ft_strjoin("/", s);
	split = ft_split(path, ':');
	while (split[i])
	{
		if (check_builtin(s))
			return (free(split), free(s1), 1);
		else if (access(ft_strjoin(split[i], s1), R_OK) == 0)
		{
			return (free(split), free(s1), 1);
		}
		i++;
	}
	return (free(split), free(s1), 0);
}

int	is_sc(char *s)
{
	if (ft_findmltpchar(s, "$|<>"))
		return (1);
	return (0);
}

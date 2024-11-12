/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:14:34 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/12 17:09:46 by tzizi            ###   ########.fr       */
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
		if (access(ft_strjoin(split[i], s1), R_OK) == 0)
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

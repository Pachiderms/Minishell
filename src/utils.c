/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:39:29 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/17 18:43:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

char	**ft_double_array_clean(char **split)
{
	char	**res;
	int		i;
	int		len;

	i = 0;
	len = 1;
	while (split[++i])
	{
		if (!ft_strchr(split[i], 34) && !ft_strchr(split[i], 39))
		len++;
	}
	res = malloc ((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		res[i] = NULL;
		i++;
	}
	return (res);
}

char	*get_rid_of(char *s, char supr)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != supr)
		len++;
	}
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != supr)
		dest[len++] = s[i];
	}
	dest[len++] = '\0';
	return (dest);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
}

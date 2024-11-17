/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:33:23 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/17 17:45:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dup(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		size;
	char	*res;

	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	res = malloc(size * sizeof(char) + 1);
	if (!res)
		return (0);
	while (s1[i] && i + j < size)
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] && i + j < size)
	{
		res[j + i] = s2[j];
		j++;
	}
	res[j + i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	else
		return (ft_dup(s1, s2));
}

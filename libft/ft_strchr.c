/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:00:39 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/18 15:41:14 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*_s;

	i = 0;
	if (!s)
		return (NULL);
	_s = (unsigned char *)s;
	while (s[i])
	{
		if (_s[i] == (unsigned char)c)
			return ((char *)(_s + i));
		i++;
	}
	if (_s[i] == (unsigned char)c)
		return ((char *)(_s + i));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:00:39 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/12 18:00:47 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*_s;

	i = 0;
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

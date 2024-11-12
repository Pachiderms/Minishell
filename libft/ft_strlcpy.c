/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:39:45 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/12 16:43:51 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	while (i + 1 < siz && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (siz > 0)
		dst[i] = '\0';
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

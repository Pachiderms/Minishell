/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:33:58 by tzizi             #+#    #+#             */
/*   Updated: 2024/05/27 14:51:49 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*z;

	if (((long)nmemb < 0 && (long)size != 0)
		|| ((long)size < 0 && (long)nmemb != 0))
		return (NULL);
	total_size = nmemb * size;
	z = malloc(total_size);
	if (z == NULL)
		return (NULL);
	else
		ft_bzero(z, total_size);
	return (z);
}

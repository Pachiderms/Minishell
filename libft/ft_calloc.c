/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:06:30 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/14 16:06:46 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*z;

	if (((long)nmemb < 0 && (long)size != 0)
		|| ((long)size < 0 && (long)nmemb != 0))
		return (NULL);
	total_size = nmemb * size;
	if (total_size == 0)
		return (NULL);
	z = malloc(total_size);
	if (z == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < nmemb)
		{
			*(unsigned char *)(z + i) = 0;
			i++;
		}
	}
	return (z);
}

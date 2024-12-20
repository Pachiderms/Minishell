/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:28:59 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/18 15:29:17 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*_s;

	i = ft_strlen(s);
	_s = (unsigned char *)s;
	while (i >= 0)
	{
		if (_s[i] == (unsigned char)c)
			return ((char *)(_s + i));
		i--;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:00:39 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/18 17:21:36 by tzizi            ###   ########.fr       */
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
char	*ft_strchrb(const char *s, int c)
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
			return (ft_substr(s, 0, i));
		i++;
	}
	if (_s[i] == (unsigned char)c)
		return (ft_substr(s, 0, i));
	return (0);
}

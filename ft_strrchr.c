/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:48:53 by zamgar            #+#    #+#             */
/*   Updated: 2024/05/31 13:36:09 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static int	ftft_strlen(const char *s, unsigned char c)
{
	int	i;

	i = 0;
	if (c != '\0')
	{
		while ((char)s[i] != '\0')
			i++;
	}
	if (c == '\0')
	{
		while ((char)s[i])
		{
			if (s[i + 1] == '\0')
				i++;
			i++;
		}
	}
	return (i);
}

static int	ft_check_other_c(char *str, unsigned char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int					i;
	unsigned char		cc;

	i = 0;
	cc = (unsigned char)c;
	if (s[0] == '\0' && cc == '\0')
		return ((char *)&s[i]);
	while ((char *)s && i < ftft_strlen(s, (unsigned char)cc))
	{
		if (s[i] == cc)
		{
			if (ft_check_other_c((char *)&s[i + 1], cc) == 0)
				return ((char *)&s[i]);
		}
		i++;
	}
	return (0);
}

/*int	main()
{
	char	s[30] = "";

	printf("%s", ft_strrchr(s, '\0'));
	return(0);
}*/

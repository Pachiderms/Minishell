/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:35:37 by zamgar            #+#    #+#             */
/*   Updated: 2024/05/31 13:25:07 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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

char	*ft_strchr(const char *s, int c)
{
	int					i;
	unsigned char		cc;

	i = 0;
	cc = (unsigned char)c;
	if (s[0] == '\0' && cc == '\0')
		return ((char *)&s[i]);
	while ((char *)s && i < ftft_strlen(s, cc))
	{
		if (s[i] == cc)
			return ((char *)&s[i + 1]);
		i++;
	}
	return (NULL);
}

/*int	main()
{
	char	*s = "hhhgthlnfvzb";
	char c = 126;
	printf("%c", c);

	printf("%s\n", ft_strchr(s, 't'));
	printf("%s\n", ft_strchr(s, 'l'));
	printf("%s\n", ft_strchr(s, 'z'));
	printf("%s\n", ft_strchr(s, 0));
	printf("%s\n\n", ft_strchr(s, 't' + 256));
	return (0);
}*/

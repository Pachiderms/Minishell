/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:14:40 by zamgar            #+#    #+#             */
/*   Updated: 2024/06/04 18:35:14 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include <stdio.h>

static size_t	ft_calc(char const *str, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 1)
		return (1);
	while (str[start] != '\0' && i < len)
	{
		i++;
		start ++;
	}
	return (i);
}

static char	*ft_gen(char *newstr, char const *str, unsigned int s, size_t len)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(str);
	while (s < strlen && i < len)
	{
		newstr[i] = str[s];
		i++;
		s++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		strlen;
	char		*n;

	strlen = ft_strlen(str);
	if (!str)
		return (NULL);
	if (start > strlen || len <= 0)
	{
		n = (char *)malloc(sizeof(char) * 1);
		if (n == NULL)
			return (NULL);
		n[0] = '\0';
		return (n);
	}
	else
	{
		if (len > strlen)
			n = (char *)malloc(sizeof(char) * strlen + 1);
		if (len <= strlen)
			n = (char *)malloc(sizeof(char) * (ft_calc(str, start, len)) + 1);
		if (n == NULL)
			return (NULL);
	}
	return (ft_gen(n, str, start, len));
}

/* int     main(void)
{
        char    *str = "lorem ipsum dolor sit amet";
        printf("%s", ft_substr(str, 7, 10));
        return (0);
} */

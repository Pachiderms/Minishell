/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:02:06 by zamgar            #+#    #+#             */
/*   Updated: 2024/05/28 16:40:10 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include <stdio.h>

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	int		s2len;
	int		totalen;
	char	*newstr;

	i = 0;
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	totalen = s1len + s2len;
	newstr = (char *)malloc(sizeof(char) * totalen + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	newstr[i] = '\0';
	ft_strcat(newstr, (char *)s1);
	ft_strcat(newstr, (char *)s2);
	i = 0;
	while (newstr[i] != '\0')
		i++;
	newstr[i] = '\0';
	return (newstr);
}

/*int	main()
{
	char	s1[20] = "Bonjour";
	char	s2[20] = "Aurevoir";

	printf("%s", ft_strjoin(s1, s2));

	return (0);
}*/

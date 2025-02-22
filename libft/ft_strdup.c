/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:03:22 by zamgar            #+#    #+#             */
/*   Updated: 2025/01/31 17:12:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include <stdio.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ss;
	char	*dest;

	i = 0;
	ss = (char *)s;
	while (ss[i] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (ss[i] != '\0')
	{
		dest[i] = ss[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*int	main()
{
	const char s[50] = "lorem ipsum dolor sit amet";
	printf("%s", ft_strdup(s));
	return (0);
}*/

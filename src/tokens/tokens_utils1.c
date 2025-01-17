/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_rid_of_quotes(char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			len++;
	}
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			dest[len++] = s[i];
	}
	dest[len++] = '\0';
	return (dest);
}

char	*cut_str(char *str, char *cut)
{
	int				i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	printf("str:%s|cut:%s\n", str, cut);
	while (s[i])
	{
		if (ft_strcmp((char *)(s + i), cut) == 0)
		{
			s[i] = '\0';
			i--;
			while (ft_isspace(s[i]))
			{
				s[i] = '\0';
				i--;
			}	
			printf("s:%s|\n", s);
			return ((char *)s);
		}
		i++;
	}
	return (NULL);
}

char	*get_rid_of(char *s, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			len++;
	}
	tmp = malloc(len * sizeof(char) + 1);
	if (!tmp)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			tmp[len++] = s[i];
	}
	tmp[len++] = '\0';
	return (tmp);
}

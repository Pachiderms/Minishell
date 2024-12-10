/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:42:11 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/18 15:41:18 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sizeup(char const *s, char c)
{
	int	size;
	int	i;

	if (s == 0 || s[0] == 0)
		return (-1);
	i = 1;
	size = 0;
	if (s[0] != c)
		size = 1;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			size++;
		i++;
	}
	return (size);
}

char	**ft_free(char **d, int start)
{
	while (start >= 0)
	{
		free(d[start]);
		start--;
	}
	free(d);
	return (0);
}

int	ft_calc(int i, int diff, char _c, char const *_s)
{
	if (diff == 1)
	{
		while (_s[i] != _c && _s[i])
			i++;
	}
	else if (diff == 0)
	{
		while (_s[i] == _c && _s[i])
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		x;
	int		size;
	char	**dest;

	i = 0;
	x = 0;
	j = 0;
	size = sizeup(s, c);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (0);
	while (size-- > 0)
	{
		i = ft_calc(i, 0, c, s);
		j = ft_calc(i, 1, c, s);
		dest[x] = ft_substr(s, i, j - i);
		if (dest[x] == NULL)
			return (ft_free(dest, x));
		x++;
		i += (j - i);
	}
	dest[x] = 0;
	return (dest);
}

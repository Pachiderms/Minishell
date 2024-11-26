/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/26 17:15:49 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sizeup(char const *s, char c)
{
	int	size;
	int	i;
    int in_quotes;

    in_quotes = 0;
	if (s == 0 || s[0] == 0)
		return (-1);
	i = 1;
	size = 0;
	if (s[0] != c)
		size = 1;
	while (s[i])
	{
        if (s[i] == 34 || s[i] == 39)
        {
            i++;
            while (s[i] && (s[i] == 34 && s[i] == 39))
            {
                size++;
                i++;
            }
        }
		if (s[i] != c && s[i - 1] == c)
			size++;
		i++;
	}
    printf("size=%d\n", size);
	return (size);
}

char	**ft_free_split(char **d, int start)
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

char	**ft_split_k_q_s(char const *s, char c)
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
			return (ft_free_split(dest, x));
		x++;
		i += (j - i);
	}
	dest[x] = 0;
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/14 12:49:02 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sizeup_no_space(char const *s)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (ft_isspace(s[i]) == 1)
			i++;
	while (s[i])
	{
		if (ft_isspace(s[i]) == 1)
		{
			while (ft_isspace(s[i]) == 1)
				i++;
			if (s[i])
				size++;
		}
		if (s[i] == 34 || s[i] == 39)
		{
			i++;
			size++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
			{
                size++;
				i++;
			}
			if (s[i] == 34 || s[i] == 39)
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*get_rid_of_spaces(char const *s)
{
	int	i = 0;
	int	j;
	int size;
	char *no_space;

	size = sizeup_no_space(s);
	no_space = malloc(sizeof(char) * size + 1);
	if (!no_space)
		return (NULL);
	i = 0;
	j = 0;
	while (ft_isspace(s[i]) == 1)
			i++;
	while (j < size)
	{
		if (ft_isspace(s[i]) == 1)
		{
			while (ft_isspace(s[i]) == 1)
				i++;
			if (s[i])
				no_space[j++] = ' ';
		}
		if (s[i] == 34 || s[i] == 39)
		{
			no_space[j++] = s[i];
			i++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
			{
                no_space[j++] = s[i];
				i++;
			}
			if (s[i] == 34 || s[i] == 39)
				no_space[j++] = s[i];
		}
		else
			no_space[j++] = s[i];
		i++;
	}
	no_space[j] = '\0';
	return (no_space);
}

char	**ft_free_split_k_q_s(char **d, int start)
{
	while (start >= 0)
	{
		free(d[start]);
		start--;
	}
	free(d);
	return (0);
}

int	check_quotes(char const *s, char q)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == q)
			quotes++;
		i++;
	}
	return (quotes % 2 == 0);
}

int	ft_calc_k_q_s(int i, int diff, char _c, char const *_s)
{
	int	j;

	j = 0;
	if (diff == 1)
	{
		while (_s[i] != _c && _s[i])
		{
			j = i + 1;
			if (_s[i] == 34 || _s[i] == 39)
			{
				if (!check_quotes(&_s[i], _s[i]))
					return (-1);
				while (_s[j] != _s[i] && _s[j])
					j++;
				i = j + 1;
			}
			else
				i++;
		}
	}
	else if (diff == 0)
	{
		while (_s[i] == _c && _s[i])
			i++;
	}
	return (i);
}

int	count_words(char *no_space)
{
	int i = 0;
	int word=0;

	while (no_space[i])
	{
		if (ft_isspace(no_space[i]) == 1)
		{
			word++;
			i++;
		}
		if (no_space[i] == 34 || no_space[i] == 39)
		{
			i++;
			while (no_space[i] && (no_space[i] != 34 && no_space[i] != 39))
				i++;
			word++;
		}
		i++;
	}
	return (word + 1);
}

char	**ft_split_k_q_s(t_main *main, char const *s, char c)
{
	int		i;
	int		j;
	int		x;
	char	**dest;

	i = 0;
	x = 0;
	j = 0;
	char *no_space = get_rid_of_spaces(s);
	dest = malloc((count_words(no_space) + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (0);
	while (no_space[i])
	{
		i = ft_calc_k_q_s(i, 0, c, no_space);
		j = ft_calc_k_q_s(i, 1, c, no_space);
		dest[x] = get_rid_of_quotes(ft_substr(no_space, i, j - i));
		if (dest[x] == NULL || j < 0)
			return (ft_free_split_k_q_s(dest, x));
		x++;
		i += (j - i);
	}
	dest[x] = 0;
	main->split_len = x;
	return (dest);
}

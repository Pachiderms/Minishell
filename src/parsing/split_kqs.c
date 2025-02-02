/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_kqs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:12:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/02 16:15:09 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_free_split_k_q_s(char **d, int start)
{
	start--;
	while (start >= 0)
	{
		free(d[start]);
		start--;
	}
	free(d);
	return (0);
}

int	ft_calc_k_q_s(int i, int diff, char _c, char const *_s) // trop de lignes
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
	int	i;
	int	word;

	i = 0;
	word = 0;
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

char	**ft_split_k_q_s(t_main *main, char const *s, char c) // trop de lignes
{
	int		i;
	int		j;
	int		x;
	char	**dest;
	char	*no_space;
	int		size;

	i = 0;
	x = 0;
	j = 0;
	no_space = get_rid_of_spaces(s);
	if (check_open_quotes(no_space, main) == 0)
		return (NULL);
	printf("no space before dollar : <%s>\n", no_space);
	no_space = replace_dollar(no_space, main);
	printf("no space after dollar : <%s>\n\n", no_space);
	no_space = handle_sc_c(no_space, main);
	no_space = get_rid_of_spaces(no_space);
	printf("no space : %s\n", no_space);
	size = count_words(no_space);
	if (size <= 0)
		return (NULL);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (free(no_space), NULL);
	while (no_space[i])
	{
		i = ft_calc_k_q_s(i, 0, c, no_space);
		j = ft_calc_k_q_s(i, 1, c, no_space);
		dest[x] = get_rid_of_quotes(ft_substr(no_space, i, j - i));
		printf("no_space[%d] adter rid quotes : <%s>\n", x, dest[x]);
		if (dest[x++] == NULL || j < 0)
			return (ft_free_split_k_q_s(dest, x));
		i += (j - i);
	}
	printf("\n");
	dest[x] = 0;
	return (free(no_space), dest);
}
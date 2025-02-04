/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_kqs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:12:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 03:16:32 by zamgar           ###   ########.fr       */
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
	if (ft_strcmp(no_space, "") == 0)
		return (0);
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
	get_close_quotes(no_space, main);
	no_space = replace_dollar(no_space, main);
	no_space = handle_sc_c(no_space, main);
	if (!main->cmd_quotes)
		main->cmd_quotes = ft_strdup(no_space);
	if (!main->cmd_no_quotes)
		main->cmd_no_quotes = get_rid_of_quotes(ft_strdup(no_space));
	printf("quotes : <%s>\n", main->cmd_quotes);
	printf("no_quotes : <%s>\n", main->cmd_no_quotes);
	char *tmp = get_rid_of_spaces(no_space);
	free(no_space);
	size = count_words(tmp);
	if (size <= 0)
		return (free(tmp), NULL);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (free(tmp), NULL);
	while (tmp[i])
	{
		i = ft_calc_k_q_s(i, 0, c, tmp);
		j = ft_calc_k_q_s(i, 1, c, tmp);
		dest[x] = get_rid_of_quotes(ft_substr(tmp, i, j - i));
		printf("no_space[%d] adter rid quotes : <%s>\n", x, dest[x]);
		if (dest[x++] == NULL || j < 0)
			return (free(tmp), ft_free_split_k_q_s(dest, x));
		i += (j - i);
	}
	printf("\n");
	dest[x] = 0;
	return (free(tmp), dest);
}
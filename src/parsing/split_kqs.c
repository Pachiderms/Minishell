/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_kqs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:12:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 01:33:46 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cook_nospace(t_main *main, char const *s)
{
	char	*no_space;
	char	*tmp;

	no_space = get_rid_of_spaces(s);
	if (check_open_quotes(no_space, main) == 0)
		return (NULL);
	printf("no space before dollar : <%s>\n", no_space);
	get_close_quotes(no_space, main);
	no_space = replace_dollar(no_space, main);
	printf("no space after dollar : <%s>\n\n", no_space);
	no_space = handle_sc_c(no_space, main);
	tmp = get_rid_of_spaces(no_space);
	free(no_space);
	printf("no space : %s\n", tmp);
	return (tmp);
}

char	**fill_dest(char **dest, char *no_space, char c)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (no_space[i])
	{
		i = ft_calc_k_q_s(i, 0, c, no_space);
		j = ft_calc_k_q_s(i, 1, c, no_space);
		dest[x] = get_rid_of_quotes(ft_substr(no_space, i, j - i));
		printf("no_space[%d] adter rid quotes : <%s>\n", x, dest[x]);
		if (dest[x++] == NULL || j < 0)
			return (free(no_space), ft_free_split_k_q_s(dest, x), NULL);
		i += (j - i);
	}
	dest[x] = 0;
	return (free(no_space), dest);
}

char	**ft_split_k_q_s(t_main *main, char const *s, char c)
{
	char	**dest;
	char	*no_space;
	int		size;

	dest = NULL;
	no_space = cook_nospace(main, s);
	size = count_words(no_space);
	if (size <= 0)
		return (NULL);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (free(no_space), NULL);
	return (fill_dest(dest, no_space, c));
}

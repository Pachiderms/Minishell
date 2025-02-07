/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_kqs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:12:00 by marvin            #+#    #+#             */
/*   Updated: 2025/02/07 19:14:13 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cook_nospace(t_main *main, char const *s)
{
	char	*no_space;
	char	*tmp;

	no_space = get_rid_of_spaces(s);
	no_space = replace_dollar(no_space, main);
	main->dollars_ok = 1;
	if (!no_space)
		return (NULL);
	no_space = handle_sc_c(no_space, main);
	free(main->cmd_quotes);
	main->cmd_quotes = NULL;
	main->cmd_quotes = ft_strdup(no_space);
	tmp = get_rid_of_spaces(no_space);
	free(no_space);
	return (tmp);
}

char	**fill_dest(char **dest, char *no_space, char c, t_main *main)
{
	int		i;
	int		j;
	int		x;
	char	*tmp;

	i = 0;
	j = 0;
	x = 0;
	while (no_space[i])
	{
		i = ft_calc_k_q_s(i, 0, c, no_space);
		j = ft_calc_k_q_s(i, 1, c, no_space);
		tmp = ft_substr(no_space, i, j - i);
		main->in_quotes[x] = 0;
		if (ft_strchr(tmp, 34) || ft_strchr(tmp, 39))
			main->in_quotes[x] = 1;
		dest[x] = get_rid_of_quotes(tmp);
		free(tmp);
		if (dest[x++] == NULL || j < 0)
			return (free(no_space), ft_free_split_k_q_s(dest, x), NULL);
		main->in_quotes[x] = -1;
		i += (j - i);
	}
	dest[x] = 0;
	return (free(no_space), dest);
}

char	*cook_nospace2(t_main *main, char const *s)
{
	char	*no_space;
	char	*tmp;

	no_space = get_rid_of_spaces(s);
	no_space = handle_sc_c(no_space, main);
	tmp = get_rid_of_spaces(no_space);
	free(no_space);
	return (tmp);
}

char	**fill_dest2(char **dest, char *no_space, char c, t_main *main)
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
		main->in_quotes[x] = 0;
		dest[x] = ft_substr(no_space, i, j - i);
		if (dest[x++] == NULL || j < 0)
			return (free(no_space), ft_free_split_k_q_s(dest, x), NULL);
		i += (j - i);
	}
	dest[x] = 0;
	return (free(no_space), dest);
}

char	**ft_split_k_q_s(t_main *main, char const *s, char c, int rmquotes)
{
	char	**dest;
	char	*no_space;
	int		size;

	dest = NULL;
	if (!main->dollars_ok)
		no_space = cook_nospace(main, s);
	else
		no_space = cook_nospace2(main, s);
	size = count_words(no_space);
	if (size <= 0 && no_space)
		free(no_space);
	if (size <= 0)
		return (NULL);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (free(no_space), NULL);
	if (rmquotes)
		return (fill_dest(dest, no_space, c, main));
	else
		return (fill_dest2(dest, no_space, c, main));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:09:58 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/04 01:16:22 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	size_up_ns_2(char const *s, size_t *i, int *size)
{
	size_t	j;
	int		si;

	j = *i;
	si = *size;
	if (s[j] == 34 || s[j] == 39)
	{
		j++;
		si++;
		while (s[j] && (s[j] != 34 && s[j] != 39))
		{
			si++;
			j++;
		}
		if (s[j] == 34 || s[j] == 39)
			si++;
	}
	else
		si++;
	*size = si;
	*i = j;
}

int	sizeup_no_space(char const *s)
{
	size_t	i;
	int		size;

	i = 0;
	size = 0;
	while (ft_isspace(s[i]) == 1)
		i++;
	while (i < ft_strlen(s))
	{
		if (ft_isspace(s[i]) == 1)
		{
			while (ft_isspace(s[i]) == 1)
				i++;
			if (s[i])
				size++;
		}
		size_up_ns_2(s, &i, &size);
		i++;
	}
	return (size);
}

void	gros_3(char const *s, char *no_space, int *k, int *l)
{
	int	i;
	int	j;

	i = *k;
	j = *l;
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
	*k = i;
	*l = j;
}

void	gros_2(char const *s, char *no_space, int *k, int *l)
{
	int	i;
	int	j;

	i = *k;
	j = *l;
	if (ft_isspace(s[i]) == 1)
	{
		while (ft_isspace(s[i]) == 1)
			i++;
		if (s[i])
			no_space[j++] = ' ';
	}
	*k = i;
	*l = j;
	gros_3(s, no_space, k, l);
}

char	*get_rid_of_spaces(char const *s)
{
	int		i;
	int		j;
	int		size;
	char	*no_space;

	i = 0;
	if (!s)
		return (NULL);
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
		gros_2(s, no_space, &i, &j);
		i++;
	}
	no_space[j] = '\0';
	return (no_space);
}

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

int	sizeup_no_space(char const *s) // trop de lignes
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

char	*get_rid_of_spaces(char const *s) // trop de lignes
{
	int		i;
	int		j;
	int		size;
	char	*no_space;

	i = 0;
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

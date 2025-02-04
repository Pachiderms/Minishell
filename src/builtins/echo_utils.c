/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:51:44 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 07:24:48 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	regular_fornl(char c, int space)
{
	if (space)
	{
		if (c != 'n' && c != '-')
			return (0);
		return (1);
	}
	return (c == 'n');
}

int	check_after_nl(char *s)
{
	int	i;
	int	j;
	int	space;

	i = 2;
	j = 0;
	space = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_isspace(s[i]) && !space)
			j = i;
		while (ft_isspace(s[i]))
		{
			space = 1;
			i++;
		}
		if (!regular_fornl(s[i], space))
			return (j);
		if (!ft_strncmp(&s[i], "-n", 2) && space)
			space = 0;
		i++;
	}
	return (j);
}

int	is_tn(char *s)
{
	if (!s)
		return (0);
	if (*s != '-')
		return (0);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

char	*find_newline(char *s)
{
	int		i;
	char	*a_nl;

	i = -1;
	a_nl = NULL;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (!ft_isspace(s[i]))
			break ;
	}
	if (ft_strncmp(&s[i], "-n", 2) == 0)
	a_nl = &s[check_after_nl(&s[i])];
	if (is_tn(a_nl))
		return ("\0");
	if (!ft_strcmp(a_nl, s))
		return (NULL);
	return (a_nl);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:01:27 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 00:15:03 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_char(char *s, int c, int diff)
{
	int	i;

	i = 0;
	if (!diff)
	{
		while (s[i])
		{
			if (s[i] != c)
				break ;
			i++;
		}
	}
	else
	{
		while (s[i])
		{
			if (s[i] == c)
				break ;
			i++;
		}
	}
	return (i);
}

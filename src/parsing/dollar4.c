/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cut_str(char *str, char *cut)
{
	int				i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	if (!cut || !str)
		return (str);
	while (s[i])
	{
		if (ft_strcmp((char *)(s + i), cut) == 0)
		{
			s[i] = '\0';
			i--;
			return ((char *)s);
		}
		i++;
	}
	return (NULL);
}

void	update_sq_pos(t_main *main, int r, int r1, int diff)
{
	while (main->s_qs[r] != -1)
	{
		main->s_qs[r] += diff;
		r++;
	}
	while (main->d_qs[r1] != -1)
	{
		main->d_qs[r1] += diff;
		r1++;
	}
}

void	update_dq_pos(t_main *main, int r, int r1, int diff)
{
	while (main->s_qs[r] != -1)
	{
		main->s_qs[r] -= diff;
		r++;
	}
	while (main->d_qs[r1] != -1)
	{
		main->d_qs[r1] -= diff;
		r1++;
	}
}

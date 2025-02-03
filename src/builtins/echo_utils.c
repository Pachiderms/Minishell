/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:51:44 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/03 17:33:58 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_arg_solo(char *s, char **tmp, int to_print)
{
    int     i;
	int		j;

    i = 0;
    if (!s)
            return ;
    while(++i < (int)ft_strlen(s) - 1)
	{
		j = i;
		while (i < (int)ft_strlen(s) - 1)
        {
            if (ft_isspace(s[i]))
                break ;
			i++;
        }
        if (!ft_isspace(s[i - 1]))
        {
               printf("%d %s\n", i, &s[i]);
			break ;
        }
	}
    if (to_print)
        *tmp = ft_substr(s, j, i - j);
    else
        *tmp = ft_substr(s, 0, i);
}

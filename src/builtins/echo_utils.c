/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:51:44 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/03 21:54:47 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_after_nl(char *s)
{
    int i;
    int space;

    i = 2;
    space = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (!space && s[i] != 'n')
            return (ft_isspace(s[i]));
        while (ft_isspace(s[i]))
        {
            space = 1;
            i++;
        }
        if (!ft_strncmp(&s[i], "-n", 2))
        {
            space = 0;
            i += 2;
        }
        i++;
    }
    return (1);
}

char    *find_newline(char *s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        if (!ft_isspace(s[i]))
            break   ;
    }
    if (ft_strncmp(&s[i], "-n", 2) == 0)
    {
        printf("check %d\n", check_after_nl(&s[i]));
    }
    return (NULL);
}

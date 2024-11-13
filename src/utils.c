/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:39:29 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/13 18:42:52 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

char    *super_join(char *s1, char *s2, int space)
{
    int i;
    int j;

    
}

char    *get_rid_of(char *s, char supr)
{
    int     i;
    int     len;
    char    *dest;

    i = 0;
    len = 0;
    while (s[++i])
    {
        if (s[i] != supr)
            len++;
    }
    dest = malloc(len * sizeof(char) + 1);
    if (!dest)
        return (0);
    i = 0;
    len = 0;
    while (s[i])
    {
        if (s[i] != supr)
            dest[len++] = s[i];
        i++;
    }
    dest[len] = '\0';
    return (dest);
}

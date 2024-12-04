/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:17:54 by zamgar            #+#    #+#             */
/*   Updated: 2024/05/31 14:55:31 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include <stdio.h>
//#include <string.h>

/* void    print_env(char **env)
{
    int i = 0;
    while (i < 49)
    {
        printf("%s\n", env[i]);
        i++;
    }
} */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
    size_t ok = -2;
	char	*ss1;
	char	*ss2;

	i = 0;
	ss1 = (char *)s1;
	ss2 = (char *)s2;
    if (n == 0)
		return (0);
	n = n - 1;
    if (n == ok)
    {
        while (ss1[i] == ss2[i] && ss1[i] != '\0' && ss2[i] != '\0')
		    i++;
	    return ((unsigned char)ss1[i] - (unsigned char)ss2[i]);
    }
	while (ss1[i] == ss2[i] && ss1[i] != '\0' && ss2[i] != '\0' && i < n)
		i++;
	return ((unsigned char)ss1[i] - (unsigned char)ss2[i]);
} 

/* void    print_ascii_order(char **env)
{
    int i = 0;
    char *tmp;

    while (i < 49)
    {
        if (ft_strncmp(env[i], env[i + 1]) > 0)
        {
            tmp = env[i + 1];
            env[i + 1] = env[i];
            env[i] = tmp;
            i = 0;
        }
        i++;
    }
}

int     main(int argc, char *argv[], char **env)
{
	//printf("%d\n", ft_strncmp("aaaa", "aaa"));
	print_ascii_order(env);
	print_env(env);
	return (0);
} */

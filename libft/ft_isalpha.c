/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:09:23 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/05 18:10:30 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*int	main()
{
	int i;
	i = 0;
   	while (i <= 47)
    	{
        	printf("%d", ft_isalpha(i));
        	i++;
    	}
    	printf("\n");
	return (0);
}*/

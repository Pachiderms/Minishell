/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:08:33 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/06 11:44:20 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//#include <stdio.h>

size_t	ft_atoi(const char *str)
{
	int		i;
	size_t	nbr;
	size_t	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

/*int	main() 
{
	const char	str[30] = "-+48";
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
	return (0);
}*/

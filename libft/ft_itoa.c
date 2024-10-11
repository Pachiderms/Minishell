/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:10:45 by tzizi             #+#    #+#             */
/*   Updated: 2024/05/27 15:31:18 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			return (1 + count_size(n / 10));
		}
		else
		{
			return (1 + count_size(-n));
		}
	}
	else if (n / 10 == 0)
		return (1);
	else
	{
		return (1 + count_size(n / 10));
	}
}

char	*ft_intmin(int n, char *_res)
{
	int		size;
	int		i;
	char	*res;

	free(_res);
	n += 1;
	i = 0;
	size = count_size(n);
	res = malloc(size * sizeof(char) + 1);
	if (res == NULL)
		return (0);
	res[0] = '-';
	n *= -1;
	res[size] = '\0';
	while (size > 1)
	{
		if (i == 0)
			res[size - 1] = ((n % 10) + 1) + 48;
		else
			res[size - 1] = (n % 10) + 48;
		n /= 10;
		i++;
		size--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int		size;
	int		i;
	char	*res;

	i = 0;
	size = count_size(n);
	res = malloc(size * sizeof(char) + 1);
	if (res == NULL)
		return (0);
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_intmin(n, res));
		res[0] = '-';
		n *= -1;
		i++;
	}
	res[size] = '\0';
	while (size > 0 + i)
	{
		res[size - 1] = (n % 10) + 48;
		n /= 10;
		size--;
	}
	return (res);
}

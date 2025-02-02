/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:21:31 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/23 11:48:48 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sub(const char *str, const char *tf, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (tf[j] && str[i] == tf[j])
	{
		i++;
		j++;
	}
	if (tf[j] == '\0' && i <= len)
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	found;

	i = 0;
	found = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0' && !found)
	{
		if (big[i] == little[0])
		{
			found = sub(big, little, i, len);
		}
		i++;
	}
	if (found)
		return ((char *)&big[i - 1]);
	else
		return (0);
}

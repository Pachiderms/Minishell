/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:11:51 by zamgar            #+#    #+#             */
/*   Updated: 2024/05/27 16:15:36 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

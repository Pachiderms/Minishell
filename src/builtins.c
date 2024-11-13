/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:31:14 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/13 14:52:29 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int    ft_echo(t_token *tokens, int fd)
{
    int i;
    int nl;

    i = 1;
    if (ft_strcmp(tokens[0].value, "echo") != 0)
        return (-1);
    tokens++;
    while (tokens[0].type == argument)
    {
        if (!ft_strcmp(tokens[0].value, "-n"))
        {
            nl = 1;
            tokens++;
        }
        if (fd == 1)
            ft_putstr_fd(tokens[0].value, fd);
        tokens++;
    }
    return (1);
}
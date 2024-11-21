/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:03:05 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/21 14:58:50 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_fork(t_main *main, char **split)
{
    pid_t   fork_id;
    int     i;
    char    *cmd;
    int     status;
    
    status = 0;
    i = 0;
    while (split[i] && ft_strcmp(split[i], "|") != 0
        && main->tokens[i].type != command)
        i++;
    cmd = prep_cmd_excve(main, split);
    fork_id = fork();
    if (fork_id == 0)
        execve(cmd, split, main->env);
    else
        waitpid(fork_id, &status, 0);
    free(cmd);
}

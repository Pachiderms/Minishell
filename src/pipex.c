/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:08:42 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 21:08:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_cmd_number(t_main *main, char **split)
{
    int i;
    int j;
    int cmd;

    cmd = 0;
    i = 0;
    while (split[i])
    {
        if (is_cmd(split[i], main->path))
        {
            cmd++;
            j = i + 1;
            while (split[j])
            {
                if (ft_strcmp(split[j], "|") == 0)
                    break ;
                if (main->tokens[j].type == command)
                    main->tokens[j].type = argument;
                j++;
            }
            i += (j - i - 1);
        }
        i++;
    }
    return (cmd);
}

void    ft_fork(t_main *main, char **split)
{
    pid_t   fork_id;
    char    *cmd;

    int status = 0;
    fork_id = fork();
    if (fork_id == 0)
    {
        cmd = ft_strjoin("/bin/", split[0]);
        execve(cmd, split, main->env);
    }
    else
        waitpid(fork_id, &status, 0);
    free(cmd);
}

void    pipex(t_main *main, char **split)
{
    if (main->nb_cmd < 2)
        return (ft_fork(main, split));
    else
        return ;
}

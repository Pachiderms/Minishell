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

void    prep_cmd_pipex(char **split)
{
    (void)split;
    return ;
}

void    ft_pipe(t_main *main, char **split)
{
    int fd[2];
    int child_pid;
    int status;
    char *cmd1[3] = {"/bin/ls", "-l", NULL};
    char *cmd2[3] = {"/bin/wc", "-l", NULL};

    (void)split;
    if (pipe(fd) < 0)
    {
        perror("pipe fail");
        exit (-1);
    }
    child_pid = fork();
    if (child_pid < 0)
    {
        perror ("fork fail");
        exit (-1);
    }
    if (child_pid == 0)
    {
        close(STDOUT_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execve(cmd1[0], cmd1, main->env);
    }
    else
    {
        int stat;
        waitpid(child_pid, &stat, 0);
        int pid_tmp = fork();
        if (pid_tmp == 0)
        {
            waitpid(child_pid, &status, 0);
            close(STDIN_FILENO);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execve(cmd2[0], cmd2, main->env);
        }
        else
        {
            close(fd[1]);
            close(fd[0]);
            waitpid(pid_tmp, &stat, 0);
        }
    }
}

void    pipex(t_main *main, char **split)
{
    if (main->nb_cmd < 2)
        return (ft_fork(main, split));
    else
        ft_pipe(main, split);
}

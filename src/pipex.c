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

char    *prep_process(char *s)
{
    char    *res=NULL;
    char    *tmp=NULL;

    if (ft_strchr(s, '<') || ft_strchr(s, '>'))
    {
        res = get_rid_of_spaces(s);
        tmp = get_rid_of(res, '<');
        free(res);
        res = get_rid_of(tmp, '>');
        free(tmp);
        tmp = get_rid_of_spaces(res);
        return (free(res), tmp);
    }
    return (get_rid_of_spaces(s));
}

int    ft_fork(t_main *main, char *cmd)
{
    pid_t   fork_id;
    int     fileout;
    char    **process;
    char    *_cmd;
    char    *tmp;

    tmp = NULL;
    _cmd = get_rid_of(cmd, '<');
    process = ft_split(_cmd, ' ');
    tmp = prep_process(_cmd);
    // printf("tmp:%s\n", tmp);
    fileout = get_fd(process);
    if (fileout < 0)
    {
        free_split(process);
        free(tmp);
        perror("fd");
        return (1);
    }
    fork_id = fork();
    if (fork_id == 0)
    {
        process = ft_split(tmp, ' ');
        free(tmp);
        dup2(fileout, STDOUT_FILENO);
        tmp = ft_strjoin("/usr/bin/", process[0]);
        execve(tmp, process, main->env);
    }
    else
    {
        waitpid(fork_id, NULL, 0);
        free(tmp);    
    }
    return (0);
}

int    child_process2(t_main *main, char *cmd)
{
    char    **tmp;
    char    *_cmd;
    pid_t   child_pid;
    int     fd[2];

    if (pipe(fd) < 0)
    {
        perror("pipe fail");
        return (1);
    }
    child_pid = fork();
    if (child_pid == 0)
    {
        close(fd[0]);
        _cmd = prep_process(cmd);
        tmp = ft_split(_cmd, ' ');
        char *cm = ft_strjoin("/usr/bin/", tmp[0]);
        dup2(fd[1], STDOUT_FILENO);
        execve(cm, tmp, main->env);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);    
    }
    return (0);
}

int ft_pipe2(t_main *main, char *split_pipex)
{
    int     i;
    char    **cmd;
    int     fdin;

    i = 0;
    cmd = ft_split(split_pipex, '|');
    fdin = get_fd(cmd);
    dup2(fdin, STDIN_FILENO);
    while (i < main->nb_cmd - 1)
    {
        if (child_process2(main, cmd[i]))
            return (1);
        i++;
    }
    ft_fork(main, cmd[i]);
    close(fdin);
    return (0);
}

int   pipex(t_main *main, char *split)
{
    if (main->nb_cmd < 2)
        return (ft_fork(main, split));
    else
        return (ft_pipe2(main, split));
}

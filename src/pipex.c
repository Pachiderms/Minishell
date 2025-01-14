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
        tmp = cut_str(res, &ft_strrchr(res, ' ')[1]);
        tmp = get_rid_of(tmp, '<');
        free(res);
        res = get_rid_of(tmp, '>');
        free(tmp);
        tmp = get_rid_of_spaces(res);
        return (free(res), tmp);
    }
    return (get_rid_of_spaces(s));
}

void    ft_fork(t_main *main, char *cmd)
{
    pid_t   fork_id;
    int     fileout;
    char    **process;
    char    *_cmd;
    char    *tmp;

    int status = 0;
    tmp = NULL;
    _cmd = get_rid_of(cmd, '<');
    process = ft_split(_cmd, ' ');
    tmp = prep_process(_cmd);
    printf("tmp:%s\n", tmp);
    fileout = get_fd(process);
    if (fileout < 0)
    {
        free_split(process);
        free(tmp);
        perror("fd");
        exit (-1);
    }
    fork_id = fork();
    if (fork_id == 0)
    {
        process = ft_split(tmp, ' ');
        free(tmp);
        dup2(fileout, STDOUT_FILENO);
        tmp = ft_strjoin("/usr/bin/", process[0]);
        printf("child cmd: %s\n", tmp);
        execve(tmp, process, main->env);
    }
    else
    {
        ft_putendl_fd("on attend", 1);
        waitpid(fork_id, &status, 0);
        free(tmp);
        ft_putendl_fd("on attend plus", 1);
    }
}

void    parent_process(t_main *main, char *cmd, int *fd)
{
    char    **tmp;
    char    *_cmd;
    int     fileout;
    
    tmp = ft_split(cmd, ' ');
    _cmd = prep_process(cmd);
    fileout = get_fd(tmp);
    if (fileout < 0)
    {
        free_split(tmp);
        perror("fd");
        exit (-1);
    }
    printf("_cmd:%s|\nexecuting on fd %d\n", _cmd, fileout);
    tmp = ft_split(_cmd, ' ');
    char *cm = ft_strjoin("/usr/bin/", tmp[0]);
    close(STDIN_FILENO);
    dup2(fd[0], STDIN_FILENO);
    dup2(fileout, STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    execve(cm, tmp, main->env);
}

void    child_process(t_main *main, char *cmd, int *fd)
{
    char    **tmp;
    char    *_cmd;
    int     filein;

    tmp = ft_split(cmd, ' ');
    _cmd = prep_process(cmd);
    filein = get_fd(tmp);
    if (filein < 0)
    {
        free_split(tmp);
        perror("fd");
        exit (-1);
    }
    printf("_cmd:%s|\n", _cmd);
    tmp = ft_split(_cmd, ' ');
    char *cm = ft_strjoin("/usr/bin/", tmp[0]);
    dup2(fd[1], STDOUT_FILENO);
    dup2(filein, STDIN_FILENO);
    close(fd[1]);
    close(fd[0]);
    execve(cm, tmp, main->env);
}

void    ft_pipe(t_main *main, char *split_pipex)
{
    int     fd[2];
    int     child_pid;
    char    **cmd;

    cmd = ft_split(split_pipex, '|');
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
        child_process(main, cmd[0], fd);
    }
    waitpid(child_pid, NULL, 0);
    parent_process(main ,cmd[1], fd);
}

void    child_process2(t_main *main, char *cmd)
{
    char    **tmp;
    char    *_cmd;
    int fd[2];
    int child_pid;
    
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
        _cmd = prep_process(cmd);
        printf("_cmd:%s|\n", _cmd);
        tmp = ft_split(_cmd, ' ');
        char *cm = ft_strjoin("/usr/bin/", tmp[0]);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(cm, tmp, main->env);
    }
    else
    {
        waitpid(child_pid, NULL, 0);
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
    }
}

void    ft_pipe2(t_main *main, char *split_pipex)
{
    int i;
    char **cmd = ft_split(split_pipex, '|');
    int filein;
    // int fileout;
    i = 0;
    filein = get_fd(cmd) == 1 ? 0 : get_fd(cmd);
    // fileout = get_fd(&cmd[main->nb_cmd - 1]);
    dup2(filein, STDIN_FILENO);
    while (i < main->nb_cmd - 1)
    {
        child_process2(main, cmd[i]);
        i++;
    }
    ft_putendl_fd("lat cmd", 1);
    ft_putendl_fd(cmd[i], 1);
    ft_fork(main, cmd[i]);
    close(filein);
}

void    pipex(t_main *main, char *split)
{
    if (main->nb_cmd < 2)
       return (ft_fork(main, split));
    else
        ft_pipe2(main, split);
}

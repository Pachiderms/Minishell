#include "../includes/minishell.h"

void    ft_echo(char **cmd)
{
    int i;
    int fd;
    int nl;

    i = 1;
    fd = get_fd(cmd);
    if (fd < 0)
        return ;
    if (ft_strcmp(cmd[0], "echo") != 0)
        return ;
    while (cmd[i])
    {
        if (!ft_strcmp(cmd[i], "-n"))
        {
            nl = 1;
            i++;
        }
        ft_putstr_fd(cmd[i], fd);
        i++;
    }
    if (nl)
        ft_putsr_fd("\n", fd);
    return ;
}

#include "../includes/minishell.h"

/* int    ft_echo(t_token *tokens, int fd)
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
} */
#include "../includes/minishell.h"

void    sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    return ;
}

void    sigquit(int sig)
{
    (void)sig;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    printf("\033[K");
    return ;
}

void init_signals()
{
    signal(SIGINT, sigint);
    signal(SIGQUIT, sigquit);
    return ;
}

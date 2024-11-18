#include "../includes/minishell.h"

void    free_old_env(char **tab, int tablen)
{
    int i;

    i = tablen - 1;
    while (i >= 0)
    {
        free(tab[i]);
        i--;
    }
    free(tab);
    tab = NULL;
    return ;
}

void    print_env(t_main *main)
{
    int i;

    i = 0;
    while (i < main->env_len)
    {
        printf("%s\n", main->env[i]);
        i++;
    }
    return ;
}

void    update_env(t_main *main, char *cmd, int update_type)
{
    if (update_type == 1)
        export(main, cmd);
    if (update_type == 2)
        unset(main, cmd);
    /* if (update_type == 3)
        cd(main, cmd); */
    return ;
}
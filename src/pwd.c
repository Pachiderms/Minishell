#include "../includes/minishell.h"

int    pwd(void)
{
    char *pwd;

    pwd = ft_strdup(getcwd(NULL, 0));
    if (pwd == NULL)
        return (free(pwd), 0);
    printf("%s\n", pwd);
    free(pwd);
    return (1);
}
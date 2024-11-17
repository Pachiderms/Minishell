#include "../includes/minishell.h"

void    print_ascii_order(t_main *main) // a voir
{
    int i = 0;
    char *tmp;
    char **sort_env;

    sort_env = (char **)malloc(sizeof(char *) * main->env_len + 1);
    while (i < main->env_len)
    {
        sort_env[i] = ft_strdup(main->env[i]);
        i++;
    }
    i = 0;
    while (i < main->env_len - 1)
    {
        if (ft_strncmp(sort_env[i], sort_env[i + 1], -1) > 0)
        {
            tmp = sort_env[i + 1];
            sort_env[i + 1] = sort_env[i];
            sort_env[i] = tmp;
            i = 0;
        }
        i++;
    }
    i = 0;
    while (i < main->env_len)
    {
        if (!(sort_env[i][0] == '_' && sort_env[i][0] == '=')) // faire en sorte de ne pas afficher le _= et de trouver cmment bouger le SSH_AUTH_SOCK en haut
            printf("%s\n", sort_env[i]);
        i++;
        
    }
    free_old_env(sort_env, main->env_len);
}

int check_syntax_export(t_main *main, char **cmd)
{
    int i;
    int j;
    int r;

    i = 0;
    r = 0;
    j = 0;
    if (cmd[0] && !cmd[1] && ft_strncmp(cmd[0], "export", -1) == 0)
        return (print_ascii_order(main), 0);
    main->cmd_highlights = (char **)malloc(sizeof(char *) * main->tokens_len - 1); // - 1 parce qu'on a déjà géré le export
    if (!main->cmd_highlights)
        return (0);
    i = 1;
    if (cmd[0] && cmd[1])
    {
        while (cmd[i] != NULL)
        {
            if (cmd[i][0] == '_' && cmd[i][1] == '=')
                main->cmd_highlights[r] = ft_strdup("0");
            else
            {
                while (cmd[i][j] != '=' && cmd[i][j])
                    j++;
                if (cmd[i][j - 1] == ' ' || j == 0 || cmd[i][j] == '\0')
                    main->cmd_highlights[r] = ft_strdup("0");
                else
                    main->cmd_highlights[r] = ft_strdup("1");
            }
            j = 0;
            i++;
        }
    }
    return (1);
}

void    export(t_main *main, char **cmd)
{
    int i = 0;
    char **tmp;
    int replace_pos;

    if (check_syntax_export(main, cmd) == 0)
        return ;
    replace_pos = check_var_exists(main, cmd);
    tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
    while (i < main->env_len)
    {
        tmp[i] = ft_strdup(main->env[i]);
        i++;
    }
    free_old_env(main->env, main->env_len);
    if (replace_pos >= 0)
        main->env = (char **)malloc(sizeof(char *) * (main->env_len) + 1);
    else
        main->env = (char **)malloc(sizeof(char *) * (main->env_len + 1) + 1);
    i = 0;
    while (i < main->env_len)
    {
        if (i == replace_pos)
        {
            main->env[i] = ft_strdup(ft_strchr(cmd, ' '));
            i++;
        }
        main->env[i] = ft_strdup(tmp[i]);
        i++;
        if (i == replace_pos)
        {
            main->env[i] = ft_strdup(ft_strchr(cmd, ' '));
            i++;
        }
    }
    free_old_env(tmp, main->env_len);
    if (replace_pos == -1)
    {
        main->env[i] = main->env[i - 1];
        main->env[i - 1] = ft_strdup(ft_strchr(cmd, ' '));
        main->env_len += 1;
    }
    return ;
}
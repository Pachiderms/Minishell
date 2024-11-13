#include "includes/minishell.h"

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

int check_var_exists(t_main *main, char *cmd)
{
    int i;
    int j;
    char *arg;

    i = 0;
    j = 0;
    arg = ft_strdup(ft_strchr(cmd, ' '));
    while (i < main->env_len)
    {
        while (main->env[i][j] != '=')
        {
            if (arg[j] == main->env[i][j])
                j++;
            else
                break ;
            if (main->env[i][j] == '=')
            {
                free(arg);
                return (i);
            }
        }
        j = 0;
        i++;
    }
    free(arg);
    return (-1);
}

////////////////////////////////////////////////////////////

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

int check_syntax_export(t_main *main, char *cmd)
{
    int i;
    char *arg;

    i = 0;
    if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'p'
        && cmd[3] == 'o' && cmd[4] == 'r'
        && cmd[5] == 't' && cmd[6] == '\0')
        {
            print_ascii_order(main);
            return (0);
        }
    if (ft_strncmp(cmd, "export ", 7) != 0)
        return (0);
    arg = ft_strdup(ft_strchr(cmd, ' '));
    if (arg[0] == '_' && arg[1] == '=')
    {
        free(arg);
        return (0);
    }
    while (arg[i] != '=' && arg[i]) 
        i++;
    if (arg[i - 1] == ' ' || i == 0 || arg[i] == '\0')
        return (0);
    free(arg);
    return (1);
}

void    export(t_main *main, char *cmd)
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

////////////////////////////////////////////////////////////

int check_syntax_unset(char *cmd)
{
    int i;
    char *arg;

    i = 0;
    if (ft_strncmp(cmd, "unset ", 6) != 0)
        return (0);
    arg = ft_strdup(ft_strchr(cmd, ' '));
    if (ft_strncmp(arg, "_", -1) == 0)
    {
        free(arg);
        return (0);
    }
    while (arg[i])
    {
        if (arg[i] == '=')
        {
            free(arg);
            return (0);
        }
        i++;
    }
    free(arg);
    return (1);
}

void    unset(t_main *main, char *cmd)
{
    int i = 0;
    int j = 0;
    int var_to_unset;
    char **tmp;

    if (check_syntax_unset(cmd) == 0)
        return ;
    var_to_unset = check_var_exists(main, cmd);
    if (var_to_unset == -1)
        return ;
    tmp = (char **)malloc(sizeof(char *) * main->env_len + 1);
    while (i < main->env_len)
    {
        tmp[i] = ft_strdup(main->env[i]);
        i++;
    }
    free_old_env(main->env, main->env_len);
    main->env = (char **)malloc(sizeof(char *) * (main->env_len - 1) + 1);
    i = 0;
    while (i < main->env_len)
    {
        if (i == var_to_unset)
            i++;
        main->env[j] = ft_strdup(tmp[i]);
        i++;
        j++;
        if (i == var_to_unset)
            i++;
    }
    free_old_env(tmp, main->env_len);
    main->env_len -= 1;
    return ;
}

////////////////////////////////////////////////////////////

void    update_env(t_main *main, char *cmd, int update_type)
{
    if (update_type == 1)
        export(main, cmd);
    if (update_type == 2)
        unset(main, cmd);
    return ;
}

void    init_env(char **env, t_main *main)
{
    int i;

    i = -1;
    main->env = NULL;
    main->env_len = 0;
    while (env[++i] != NULL)
        continue ;
    main->env_len = i;
    main->env = (char **)malloc(sizeof(char *) * main->env_len + 1);
    i = 0;
    while (i < main->env_len)
    {
        main->env[i] = ft_strdup(env[i]);
        i++;
    }
    return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
    t_main main;
    char *rl;
    char *cmd;
    int i;

    init_env(env, &main);
	while (1)
	{
		rl = readline("Prompt >");
        cmd = ft_strdup(rl);
        if (cmd[0] == 'e' && cmd[1] == 'n' && cmd[2] == 'v' && cmd[3] == '\0')
            print_env(&main);
        if (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 'r' && cmd[5] == 't')
            update_env(&main, cmd, 1);
        if (cmd[0] == 'u' && cmd[1] == 'n' && cmd[2] == 's' && cmd[3] == 'e' && cmd[4] == 't')
            update_env(&main, cmd, 2);
	}
    i = main.env_len - 1;
    while (i >= 0)
    {
        free(main.env[i]);
        i--;
    }
    free(main.env);
    main.env = NULL;
    return (0);
}
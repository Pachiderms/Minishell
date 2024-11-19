/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:26:30 by tzizi            #+#    #+#             */
/*   Updated: 2024/11/18 20:26:30 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
=======
// void    ft_free_cmd(t_main *main, char **split, char *cmd)
// {
//     int i;

//     i = 0;
//     while (i < main->tokens_len)
//     {
//         main->tokens[i].value = NULL;
//         i++;
//     }
//     free(main->tokens);
//     i = 0;
//     while (split[i])
//     {
//         split[i] = NULL;
//         i++;
//     }
//     free(split);
//     free(cmd);
// }

>>>>>>> telvin
char    *prep_cmd(char *cmd)
{
    int     i;
    char    *res;

    i = 0;
    while (cmd[i] && cmd[i] != '|')
        i++;
    res = malloc((ft_strlen(cmd) - i) * sizeof(char) + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (cmd[i] && cmd[i] != '|')
    {
        res[i] = cmd[i];
        i++;
    }
    return (res);
}

void    ft_exec(t_main *main, char **split, char *cmd)
{
    if (main->tokens[0].type == command)
    {
        if (check_builtin(main->tokens[0].value))
        {
            if (ft_strcmp(main->tokens[0].value, "env") == 0)
			    print_env(main);
		    if (ft_strcmp(main->tokens[0].value, "export") == 0)
			    update_env(main, prep_cmd(cmd), 1);
		    if (ft_strcmp(main->tokens[0].value, "unset") == 0)
			    update_env(main, prep_cmd(cmd), 2);
		    if (ft_strcmp(main->tokens[0].value, "echo") == 0)
			    ft_echo(split);
            if (ft_strcmp(main->tokens[0].value, "cmd") == 0)
			    ft_echo(split);
        }
<<<<<<< HEAD
    }
    else
=======
        else
            pipex(main, split);
        main->nb_cmd--;;
    }
    else if (cmd[0] != '\0')
>>>>>>> telvin
        printf(GREY"minishell: %s: command not found\n"RESET, main->tokens[0].value);
}

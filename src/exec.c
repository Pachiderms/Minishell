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

void    builtin(t_main *main, char **split, char *cmd)
{
    (void)cmd;
    if (ft_strcmp(main->tokens[0].value, "env") == 0 || ft_strcmp(main->tokens[0].value, "/bin/env") == 0)
		print_env(main, 0, split);
	if (ft_strcmp(main->tokens[0].value, "export") == 0)
        prep_export(main, split);
	if (ft_strcmp(main->tokens[0].value, "unset") == 0)
        prep_unset(main, split);
	if (ft_strcmp(main->tokens[0].value, "echo") == 0)
		ft_echo(split);
    if (ft_strcmp(main->tokens[0].value, "cd") == 0)
        cd(main, split);
    if (ft_strcmp(main->tokens[0].value, "pwd") == 0)
        pwd(main, split);
}

int    ft_exec(t_main *main, char **split, char *cmd)
{
    //for (int i=0; split[i];i++)
    //    printf("token type=%d\t val: %s\n", main->tokens[i].type, main->tokens[i].value);
     //printf("nb_cmd=%d\n", main->nb_cmd);
    if (main->tokens[0].type == command)
    {
        if (check_builtin(main->tokens[0].value))
            builtin(main, split, cmd);
        else
        {
            if(check_var_exists(main->env, main->env_len, "export PATH=") == -1)
                return (printf("bash: %s: No such file or directory\n", split[0]), 1);
            prep_cmd_pipex(main, split);
        }
        main->nb_cmd--;
    }
    else if (cmd[0] != '\0')
        printf(GREY"minishell: %s: command not found\n"RESET, main->tokens[0].value);
     //printf("nb_cmd=%d\n", main->nb_cmd);
    free_end_cmd(main, split);
    return (1);
}

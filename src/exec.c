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
    if (ft_strcmp(main->tokens[0].value, "env") == 0)
		main->last_exit_code = print_env(main, 0, split);
	if (ft_strcmp(main->tokens[0].value, "export") == 0)
        main->last_exit_code = prep_export(main, split);
	if (ft_strcmp(main->tokens[0].value, "unset") == 0)
        main->last_exit_code = prep_unset(main, split);
	if (ft_strcmp(main->tokens[0].value, "echo") == 0)
	    main->last_exit_code = ft_echo(main, split);
    if (ft_strcmp(main->tokens[0].value, "cd") == 0)
        main->last_exit_code = cd(main, cmd);
    if (ft_strcmp(main->tokens[0].value, "pwd") == 0)
        main->last_exit_code = pwd();
}

void    ft_exec(t_main *main, char **split, char *cmd)
{
    //printf("nb_cmd=%d\n", main->nb_cmd);
    if (main->nb_cmd >= 1)
    {
        if (check_builtin(main->tokens[0].value) && main->nb_cmd == 1)
            builtin(main, split, cmd);
        else
            main->last_exit_code = prep_cmd_pipex(main, split);
        main->nb_cmd--;
    }
    else if (cmd[0] != '\0')
        printf(GREY"minishell: %s: command not found\n"RESET, main->tokens[0].value);
     //printf("nb_cmd=%d\n", main->nb_cmd);
}

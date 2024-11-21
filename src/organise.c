/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:45:15 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/21 15:14:10 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_next_pipe(char **split, int i)
{
    while (split[i] && ft_strcmp(split[i], "|") != 0)
        i++;
    return (i);
}

char    **organise_split(t_main *main, char **split)
{
    int     i;
    int     j;
    int     cmd_index;
    char    *tmp;
    
    i = 0;
    j = find_next_pipe(split, i);
    while (i < j);
    {
        if (i + 1 == j)
            j = find_next_pipe(split, j);
        if (main->tokens[i].type == command && i != 0)
            replace_cmd(main, split, i, j);
        if (is_sc(split[i]))
            replace_in_out_file(main, split, i, j);
        i++;
    }
    return (NULL);
}

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
char    *prep_cmd_excve(t_main *main, char **split)
{
    (void)main;
    if (ft_strncmp(split[0], "/bin/", 4 ) == 0)
        return (ft_strdup(split[0]));
    return (ft_strjoin("/bin/", split[0]));
}

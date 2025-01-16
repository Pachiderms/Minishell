/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:19 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/23 14:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int prep_cmd_pipex(t_main *main, char **split)
{
    int i;
    int k;
    char    *split_pipex;

    i = 0;
    (void)split;
    // printf("split_len %d token_len %d\n", main->split_len, main->tokens_len);
    split_pipex = NULL;
    while (i <= main->tokens_len - 1)
    {
        k = i;
        while (main->tokens[i].type != 0 && i <= main->tokens_len - 1)
            i++;
        split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[i].value), " ");
        i++;
        while (i <= main->tokens_len - 1)
        {
            if (main->tokens[i].type != 1)
                break ;
            split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[i].value), " ");
            i++;
        }
        if (k <= main->tokens_len - 1
            && (ft_strcmp(main->tokens[k].value, "<") == 0 || ft_strcmp(main->tokens[k].value, "<<") == 0))
        {
            split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[k].value), " ");
            split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[k + 1].value), " ");
        }
        else if (i <= main->tokens_len - 1
            && (ft_strcmp(main->tokens[i].value, ">") == 0 || ft_strcmp(main->tokens[i].value, ">>") == 0))
        {
            split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[i].value), " ");
            split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[i + 1].value), " ");
            i += 2;
        }
        if (i <= main->tokens_len - 1)
        {
            // printf("ici : %s\n", main->tokens[i].value);
            if (ft_strcmp(main->tokens[i].value, "|") == 0)
                split_pipex = ft_strjoin_free(ft_strjoin_free(split_pipex, main->tokens[i].value), " ");
        }
        i++;
    }
    // printf("split pipex : '%s'\n", split_pipex);
    return(pipex(main, split_pipex));
}

// < infile.txt cat -l -p  | grep "ok" > outfile.txt | < infile.txt cat -l -p  | grep "ok" > outfile.txt

// < infile.txt cat -l -p  | grep ok > outfile.txt | < infile.txt cat -l -p  | grep ok > outfile.txt

/* void    prep_cmd_pipex(t_main *main, char **split)
{
    int i;
    int j;
    int k;
    char    **split_pipex;

    i = 0;
    j = 0;
    (void)split;
    printf("split_len %d token_len %d\n", main->split_len, main->tokens_len);
    split_pipex = (char **)malloc(sizeof(char *) * (main->split_len - 1) + 1);
    while (i < main->tokens_len - 1)
    {
        k = i;
        while (main->tokens[i].type != 0 && i < main->tokens_len - 1) // va jusqua la commande
            i++;
        split_pipex[j++] = ft_strdup(main->tokens[i].value);
        i++;
        while (main->tokens[i].type == 1 && i < main->tokens_len - 1) // ajoute tous les args
        {
            split_pipex[j++] = ft_strdup(main->tokens[i].value);
            i++;
        }
        if (main->tokens[k].type == 2) // si on a un sc au debut (donc infile
            split_pipex[j++] = ft_strdup(main->tokens[k + 1].value);
        else if (main->tokens[i].type == 2 && ft_strcmp(main->tokens[i].value, "|") != 0)
        {
            split_pipex[j++] = ft_strdup(main->tokens[i + 1].value);
            i += 2;
        }
        if (i < main->tokens_len - 1)
        {
            printf("ici : %s\n", main->tokens[i].value);
            if (ft_strcmp(main->tokens[i].value, "|") == 0)
                split_pipex[j++] = ft_strdup(main->tokens[i].value);
        }
        i++;
        //printf("ici2 : %s\n", main->tokens[i].value);
    }
    split_pipex[j] = NULL;
    for(i = 0;split_pipex[i];i++)
		printf("split : %s\n", split_pipex[i]);
    exit(0);
    //pipex(main, split_pipex);
    return ;
} */
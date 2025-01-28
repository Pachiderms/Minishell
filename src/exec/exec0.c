/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:19 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/28 13:05:15 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**prep_cmd_exec(t_main *main)
{
	int		i;
	int		j;
	int		k;
	char	**res;
	char	*tmp;

	res = malloc((main->nb_cmd + 2) * sizeof(char *));
	i = 0;
	k = 0;
	while (i < main->tokens_len && main->nb_cmd > 0)
	{
		j = i;
		tmp = NULL;
		while (j < main->tokens_len)
		{
			if (main->tokens[j].type == command)
				break ;
			j++;
		}
		while (i < main->tokens_len)
		{
			if (!ft_strcmp(main->tokens[i].value, "|"))
				break ;
			if (main->tokens[i].type != command)
			{
				tmp = ft_strjoin_free(tmp, " ", 0);
				tmp = ft_strjoin_free(tmp, main->tokens[i].value, 0);			
			}
			i++;
		}
		res[k++] = ft_strjoin_free(main->tokens[j].value, tmp, 1);
		i++;
	}
	res[k] = NULL;
	return (res);
}
/*
int	prep_cmd_exec(t_main *main, char **split) // trop de lignes
{
	int		i;
	int		k;
	char	*split_pipex;

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
	printf("split pipex : '%s'\n", split_pipex);
	return (pipex(main, split_pipex));
}
*/
// < infile.txt cat -l -p  | grep "ok" > outfile.txt | < infile.txt cat -l -p  | grep "ok" > outfile.txt

// < infile.txt cat -l -p  | grep ok > outfile.txt | < infile.txt cat -l -p  | grep ok > outfile.txt

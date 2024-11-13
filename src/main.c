/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:16:29 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/13 18:41:45 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/builtins.h"
#include "../includes/utils.h"

char	*PATH="/home/tzizi/.local/funcheck/host:/home/tzizi/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";

int	ft_quote(char **s, char **split, int q)
{
	int		i;
	char	*tmp;
	
	i = 1;
	*s = get_rid_of(*split, q);
	while (split[i])
	{
		if (ft_strchr(split[i], q))
		{
			tmp = ft_strjoin(" ", get_rid_of(split[i], q));
			*s = ft_strjoin(*s, tmp);
			break ;
		}
		tmp = ft_strjoin(" ", get_rid_of(split[i], q));
		*s = ft_strjoin(*s, tmp);
		i++;
	}
	return (i);
}

char	**clean_split(char **split)
{
	int		i;
	int		len;
	char	**res;
	i = 0;
	while (split[++i])
    {
        if (!ft_strchr(split[i], 34) && !ft_strchr(split[i], 39))
            len++;
    }
	res = malloc ((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], 34))
			i += ft_quote(&res[len++], &split[i], 34);
		else if (ft_strchr(split[i], 39))
			i += ft_quote(&res[len++], &split[i], 39);
		else
			res[len++] = split[i];
		i++;
	}
	res[len] = NULL;
	return (res);
}

t_token	*init_tokens(char **split)
{
	int		i;
	t_token	*tokens;

	i = 0;
	while (split[i] != NULL)
		i++;
	tokens = malloc(i * sizeof(t_token));
	if (!tokens)
		return (NULL);
	i = 0;
	while (split[i] != NULL)
	{
		if (is_cmd(split[i], PATH))
			tokens[i].type = command;
		else if (is_sc(split[i]))
			tokens[i].type = sc;
		else
			tokens[i].type = argument;
		tokens[i].value = split[i];
		i++;
	}
	return (tokens);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int		status;
	pid_t	fork_id;

	while (1)
	{
		char *cmd = readline(GREEN"minishell: "RESET);
		if (cmd)
		{
			add_history(cmd);
			char **split = ft_split(cmd, ' ');
			char **c_split = clean_split(split);
			// for (int i=0;c_split[i]!=NULL;i++)
			// {
			// 	printf("i: %d\tsplit: %s\n"
			// 		, i, c_split[i]);
			// }
			t_token	*tokens = init_tokens(c_split);
			for (int i=0;c_split[i]!=NULL;i++)
			{
				printf("token: %d\n\ttype: %d\nvalue: %s\n"
					, i, (int)tokens[i].type, tokens[i].value);
			}
			// if (!ft_strcmp(tokens[0].value, "echo"))
			// 	ft_echo(tokens, 1);
		}
		// fork_id = fork();
		// if (fork_id == 0)
		// 	execve(split[0], split, NULL);
		// else
		// 	waitpid(fork_id, &status, 0);
	}
}

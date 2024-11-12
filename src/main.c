/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:16:29 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/12 17:12:36 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/token.h"

char	*PATH="/home/tzizi/.local/funcheck/host:/home/tzizi/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";

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

char	**ft_clean_split(char **split)
{
	char	**res;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (split[i])
		i++;
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (split[i])
	{
		len = ft_strlen(split[i]);
		if ((split[i][0] == '"' && split[i][len - 1] == 34)
			|| (split[i][0] == 39 && split[i][len - 1] == 39))
			res[i] = ft_substr(split[i],
					1, len - 2);
		else
			res[i] = ft_substr(split[i],
					0, len);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int		status;
	pid_t	fork_id;

	while (1)
	{
		char *cmd = readline("Waiting for command: ");
		char **split = ft_split(cmd, ' ');
		char **c_split = ft_clean_split(split);
		t_token	*tokens = init_tokens(c_split);
		for (int i=0;c_split[i]!=NULL;i++)
		{
			printf("token: %d\n\ttype: %d\nvalue: %s\n"
				, i, (int)tokens[i].type, tokens[i].value);
		}
		// fork_id = fork();
		// if (fork_id == 0)
		// 	execve(split[0], split, NULL);
		// else
		// 	waitpid(fork_id, &status, 0);
	}
}

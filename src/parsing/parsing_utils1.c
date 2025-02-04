/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:09:58 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/04 18:30:22 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_char_to_str(char *s, char c, int _free)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = malloc((len + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i++] = c;
	res[i++] = '\0';
	if (_free)
		free(s);
	return (res);
}

char	*cmd_separate(char *s)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i + 1] == '>' || s[i + 1] == '|')
		{
			if (!ft_isspace(s[i]))
				res = add_char_to_str(res, s[i], 1);
			res = add_char_to_str(res, ' ', 1);
			i++;
		}
		res = add_char_to_str(res, s[i], 1);
		if ((s[i] == '>' || s[i] == '|')
			&& s[i + 1] != s[i])
			res = add_char_to_str(res, ' ', 1);
		i++;
	}
	return (free(s), res);
}

int	get_arg_len(char *arg)
{
	int	words;
	int	i;

	words = 0;
	i = 1;
	if (!arg)
		return (0);
	if (ft_strlen(arg) == 1 && !ft_isspace(arg[0]))
		return (1);
	while (i < (int)ft_strlen(arg) - 1)
	{
		while (i < (int)ft_strlen(arg) - 1)
		{
			if (ft_isspace(arg[i]))
				break ;
			i++;
		}
		if (!ft_isspace(arg[i - 1]))
		{
			printf("%d %s\n", i, &arg[i]);
			words++;
		}
		i++;
	}
	return (words);
}

t_cmd	*init_cmd_tokens(char **pipes, t_main *main)
{
	char	**pipe;
	t_cmd	*cmd_tokens;
	t_cmd	*tmp;
	int		i;

	pipe = ft_split_k_q_s(main, pipes[0], ' ');
	cmd_tokens = ft_lstnew(main, pipe);
	if (cmd_tokens->cmd)
		main->nb_cmd++;
	free_split(pipe);
	i = 0;
	while (++i < get_dchar_len(pipes))
	{
		pipe = ft_split_k_q_s(main, pipes[i], ' ');
		tmp = ft_lstnew(main, pipe);
		if (tmp->cmd)
			main->nb_cmd++;
		ft_lstadd_back(&cmd_tokens, tmp);
		tmp = tmp->next;
		free_split(pipe);
	}
	return (cmd_tokens);
}

int	order(char *_s, t_main *main)
{
	char	*s;
	char	**pipes;

	(void)main;
	s = get_rid_of_spaces(_s);
	if (!s || s[0] == '\0')
		return (0);
	pipes = ft_split_k_q_s(main, s, '|');
	main->cmd_tokens = init_cmd_tokens(pipes, main);
	print_t_cmd(main->cmd_tokens);
	return (free(s), free_split(pipes), 1);
}

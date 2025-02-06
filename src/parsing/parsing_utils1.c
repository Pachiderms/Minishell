/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:09:58 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/06 16:56:51 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_char_to_str(char *s, char c, int _free)
{
	char	*res;
	int		len;
	int		i;

	if (!c)
		return (s);
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
	while (i < (int)ft_strlen(arg))
	{
		while (i < (int)ft_strlen(arg))
		{
			if (ft_isspace(arg[i]))
				break ;
			i++;
		}
		if (!ft_isspace(arg[i - 1]))
		{
			words++;
		}
		i++;
	}
	return (words);
}

t_cmd	*init_cmd_tokens(char **pipes, t_main *main)
{
	t_cmd	*cmd_tokens;
	t_cmd	*tmp;
	int		i;

	if (!pipes)
		return (NULL);
	cmd_tokens = ft_lstnew(main, pipes[0]);
	if (cmd_tokens->cmd)
		main->nb_cmd++;
	i = 0;
	while (++i < get_dchar_len(pipes))
	{
		tmp = ft_lstnew(main, pipes[i]);
		if (tmp->cmd)
			main->nb_cmd++;
		ft_lstadd_back(&cmd_tokens, tmp);
		tmp = tmp->next;
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
	if (check_open_quotes(s, main) == 0)
		return (free(s), 0);
	get_close_quotes(s, main);
	pipes = ft_split_k_q_s(main, s, '|', 0);
	main->cmd_tokens = init_cmd_tokens(pipes, main);
	if (!main->cmd_tokens)
		return (free(s), free_split(pipes), 0);
	if (!check_global_syntax(s, main))
		return (free_split(pipes), free(s), 0);
	if (main->noFile)
		return (0);
	return (free(s), free_split(pipes), 1);
}

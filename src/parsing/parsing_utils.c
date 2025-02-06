/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/06 18:34:15 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_dchar_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

void	find_args_res(char **res, char **arg)
{
	*res = ft_strjoin_free(*res, *arg, 0);
	if (*(arg + 1))
		*res = ft_strjoin_free(*res, " ", 0);
}

char	*find_args(char *_s, t_main *main, char *cmd, t_cmd *token)
{
	int		i;
	char	*res;
	char	*previous;
	char	**s;

	i = -1;
	res = NULL;
	previous = NULL;
	if (!_s)
		return (NULL);
	s = ft_split_k_q_s(main, _s, ' ', 1);
	if (!s)
		return (NULL);
	get_fd_in(s, main, token);
	while (s[++i])
	{
		if (((!is_cmd(s[i], main->path) || ft_strcmp(s[i], cmd) != 0)
				&& !ft_strnstr(s[i], "<<", ft_strlen(s[i]))
				&& ft_strcmp(previous, "<<") != 0)
			|| (was_in_quotes(s[i], main, ft_substr(s[i], 0, ft_strlen(s[i]))) && !is_cmd(s[i], main->path))
			|| (!ft_strcmp(s[i], cmd) && !ft_strcmp(cmd, "exit")))
			find_args_res(&res, &s[i]);
		previous = s[i];
	}
	return (free_split(s), res);
}

char	*find_cmd(char *_s, t_main *main)
{
	int		i;
	char	**s;
	char	*cmd;
	int		eof;

	i = 0;
	eof = 0;
	if (!_s)
		return (NULL);
	s = ft_split_k_q_s(main, _s, ' ', 1);
	if (!s)
		return (NULL);
	cmd = NULL;
	while (s[i])
	{
		if (get_next(&s[i], "<<") && eof != 1)
			eof = i;
		if (is_cmd(s[i], main->path) && !cmd && eof != (i - 1))
		{
			eof = 0;
			cmd = ft_strdup(s[i]);
		}
		i++;
	}
	return (free_split(s), cmd);
}

char	*find_heredoc_eof(char *_s, t_main *main)
{
	int		i;
	char	**s;
	char	*hd;

	i = 0;
	hd = NULL;
	if (!_s)
		return (NULL);
	s = ft_split_k_q_s(main, _s, ' ', 1);
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (main->in_quotes[i] != 1)
		{
			if (get_next(&s[i], "<<"))
				hd = ft_strjoin_free(hd, get_next(&s[i], "<<"), 0);
		}
		i++;
	}
	return (free_split(s), hd);
}

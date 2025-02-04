/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/04 08:37:33 by zamgar           ###   ########.fr       */
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

char	*find_args(char **s, t_main *main)
{
	int			i;
	char		*res;
	char		*previous;

	i = 0;
	res = NULL;
	previous = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		s[i] = get_rid_of_quotes(s[i]);
		if (!is_cmd(s[i], main->path)
			&& !ft_strnstr(s[i], "<<", ft_strlen(s[i]))
			&& ft_strcmp(previous, "<<") != 0)
		{
			main->arg[main->k++] = ft_strdup(s[i]);
			res = ft_strjoin_free(res, s[i], 0);
			if (s[i + 1])
				res = ft_strjoin_free(res, " ", 0);
		}
		previous = s[i];
		i++;
	}
	main->arg[main->k] = NULL;
	return (res);
}

char	*find_cmd(char **s, t_main *main)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		s[i] = get_rid_of_quotes(s[i]);
		if (is_cmd(s[i], main->path))
			return (ft_strdup(s[i]));
		i++;
	}
	return (NULL);
}

char	*find_heredoc_eof(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		s[i] = get_rid_of_quotes(s[i]);
		if (get_next(&s[i], "<<"))
			return (ft_strdup(get_next(&s[i], "<<")));
		i++;
	}
	return (NULL);
}

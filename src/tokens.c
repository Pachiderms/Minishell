/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:11 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_double_array_clean(char **split)
{
	char	**res;
	int		i;
	int		len;

	i = 0;
	len = 1;
	while (split[++i])
	{
		if (!ft_strchr(split[i], 34) && !ft_strchr(split[i], 39))
		len++;
	}
	res = malloc ((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		res[i] = NULL;
		i++;
	}
	return (res);
}

char	**clean_split(t_main *main, char **split)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = 0;
	res = ft_double_array_clean(split);
	if (!res)
		return (NULL);
	while (split[i])
	{
		if (ft_strchr(split[i], 34) || ft_strchr(split[i], 39))
			i += ft_quote(&res[len], &split[i]);
		else
		{
			res[len] = split[i];
			i++;
		}
		len++;
	}
	res[len] = NULL;
	main->split_len = len;
	free(split);
	return (res);
}

int	init_tokens(char **split, t_main *main)
{
	int		i;
	i = 0;
	if (!split)
		return (0);
	while (split[i] != NULL)
		i++;
	main->tokens_len = i;
	main->tokens = malloc(i * sizeof(t_token));
	if (!main->tokens)
		return (0);
	i = -1;
	while (split[++i] != NULL)
	{
		if (is_cmd(split[i], main->path))
			main->tokens[i].type = command;
		else if (is_sc(split[i]) > 0)
		{
			if (!handle_sc(main, split, i))
				return (0);
		}
		else
			main->tokens[i].type = argument;
		main->tokens[i].value = split[i];
	}
	main->nb_cmd = get_cmd_number(main, split);
	return (1);
}

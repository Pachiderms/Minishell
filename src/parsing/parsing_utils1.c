/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/30 18:06:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_end(char *kqs, int start)
{
	while (kqs[start])
	{
		if (!ft_strncmp(&kqs[start], "<", 1) || !ft_strncmp(&kqs[start], ">", 1)
			|| !ft_strncmp(&kqs[start], "|", 1))
		{
			break ;
		}
		start++;
	}
	return (start);
}

int	to_separer(char *s)
{
	if (ft_strchr(s, '<') || ft_strchr(s, '>')
		|| ft_strchr(s, '|'))
		return (1);
	return (0);
}

int	order_redirect(char **res, char *kqs_cmd)
{
	int		start;
	int		end;
	char	*sub;
	char	redirect[2];

	if (!kqs_cmd)
		return (-1);
	start = start_end(kqs_cmd, 0);
	end = start_end(kqs_cmd, start + 1);
	redirect[0] = kqs_cmd[start];
	redirect[1] = '\0';
	sub = ft_substr(kqs_cmd, 0, end - start);
	if (!ft_strchr(sub, redirect[0]))
		*res = ft_strjoin_free(*res, sub, 0);
	else
		*res = ft_strjoin_free(*res, cut_str(sub, ft_strrchr(sub, redirect[0])), 0);
	free(sub);
	*res = ft_strjoin_free(*res, " ", 0);
	*res = ft_strjoin_free(*res, redirect, 0);
	*res = ft_strjoin_free(*res, " ", 0);
	sub = ft_substr(kqs_cmd, start, end - start);
	*res = ft_strjoin_free(*res, &sub[1], 0);
	if (to_separer(&kqs_cmd[end]))
		return (free(sub), end);
	return (free(sub), -1);
}

char	*order(char *s)
{
	int		i;
	int		j;
	char	**kqs_tmp;
	char	*res;

	i = 0;
	kqs_tmp = ft_split(s, ' ');
	res = NULL;
	while (kqs_tmp[i])
	{
		if (to_separer(kqs_tmp[i]))
		{
			j = order_redirect(&res, kqs_tmp[i]);
			while (j > 0)
				j = order_redirect(&res, &kqs_tmp[i][j]);
		}
		else
		{
			res = ft_strjoin_free(res, kqs_tmp[i], 0);
		}
		res = ft_strjoin_free(res, " ", 0);
		i++;
	}
	return (free_split(kqs_tmp), res);
}

int	sizeup_no_space(char const *s) // trop de lignes
{
	size_t	i;
	int		size;

	i = 0;
	size = 0;
	while (ft_isspace(s[i]) == 1)
		i++;
	while (i < ft_strlen(s))
	{
		if (ft_isspace(s[i]) == 1)
		{
			while (ft_isspace(s[i]) == 1)
				i++;
			if (s[i])
				size++;
		}
		if (s[i] == 34 || s[i] == 39)
		{
			i++;
			size++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
			{
				size++;
				i++;
			}
			if (s[i] == 34 || s[i] == 39)
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*get_rid_of_spaces(char const *s) // trop de lignes
{
	int		i;
	int		j;
	int		size;
	char	*no_space;

	i = 0;
	size = sizeup_no_space(s);
	no_space = malloc(sizeof(char) * size + 1);
	if (!no_space)
		return (NULL);
	i = 0;
	j = 0;
	while (ft_isspace(s[i]) == 1)
		i++;
	while (j < size)
	{
		if (ft_isspace(s[i]) == 1)
		{
			while (ft_isspace(s[i]) == 1)
				i++;
			if (s[i])
				no_space[j++] = ' ';
		}
		if (s[i] == 34 || s[i] == 39)
		{
			no_space[j++] = s[i];
			i++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
			{
				no_space[j++] = s[i];
				i++;
			}
			if (s[i] == 34 || s[i] == 39)
				no_space[j++] = s[i];
		}
		else
			no_space[j++] = s[i];
		i++;
	}
	no_space[j] = '\0';
	return (no_space);
}

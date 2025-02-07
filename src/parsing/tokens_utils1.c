/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2025/02/07 18:44:33 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_rid_of_quotes(char *s)
{
	int		i;
	char	*dest;
	char	q;

	i = 0;
	if (!s)
		return (NULL);
	dest = NULL;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == 34 || s[i] == 39)
		{
			q = s[i++];
			while (s[i] != q && s[i])
				dest = add_char_to_str(dest, s[i++], 1);
			i++;
		}
		if (i > (int)ft_strlen(s))
			break ;
		if (s[i] != 34 && s[i] != 39)
			dest = add_char_to_str(dest, s[i], 1);
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	return (dest);
}

char	*get_rid_of(char *s, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
	if (!s)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c)
			len++;
	}
	tmp = malloc(len * sizeof(char) + 1);
	if (!tmp)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			tmp[len++] = s[i];
	}
	tmp[len++] = '\0';
	return (tmp);
}

char	*get_cmd(char *path)
{
	if (ft_strlen(path) >= 5)
	{
		if (!ft_strncmp(path, "/bin/", 5))
			return (&path[5]);
	}
	else if (ft_strlen(path) >= 8)
	{
		if (!ft_strncmp(path, "/usr/bin/", 8))
			return (&path[8]);
	}
	return (path);
}

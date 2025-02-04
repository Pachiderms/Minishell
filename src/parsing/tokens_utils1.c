/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2025/02/04 04:15:28 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	s_len(char *s)
{
	int		i;
	int		len;
	char	q;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			q = s[i++];
			while (s[i] != q && s[i])
			{
				len++;
				i++;
			}
			i++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] != 34 && s[i] != 39)
			len++;
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	return (len);
}

char	*get_rid_of_quotes(char *s)
{
	int		i;
	int		len;
	char	*dest;
	char	q;

	i = 0;
	if (!s)
		return (NULL);
	len = s_len(s);
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (free(s), NULL);
	len = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			q = s[i++];
			while (s[i] != q && s[i])
				dest[len++] = s[i++];
			i++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] != 34 && s[i] != 39)
			dest[len++] = s[i];
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	dest[len] = '\0';
	return (free(s), dest);
}

char	*get_rid_of(char *s, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
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
	if (!ft_strncmp(path, "/bin/", 5))
		return (&path[5]);
	else if (!ft_strncmp(path, "/usr/bin/", 8))
		return (&path[8]);
	else
		return (path);
}

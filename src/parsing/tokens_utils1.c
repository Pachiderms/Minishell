/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2025/02/01 13:25:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_rid_of_quotes(char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		//printf("i : %d\n", i);
		if (s[i] == 34 || s[i] == 39)
		{
			char q = s[i];
			//printf("i before passing : %d\n", i);
			i++;
			while (s[i] != q && s[i])
			{
				//printf("%c", s[i]);
				len++;
				i++;
			}
			i++;
			//printf("i after passing : %d\n", i);
		}
		if (s[i] == '\0')
			break ;
		if (s[i] != 34 && s[i] != 39)
		{
			//printf("%c", s[i]);
			len++;
		}
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	//printf("\nlen : %d\n", len);
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			char q = s[i];
			i++;
			while (s[i] != q && s[i])
			{
				dest[len++] = s[i];
				i++;
			}
			i++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] != 34 && s[i] != 39)
			dest[len++] = s[i];
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	dest[len++] = '\0';
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

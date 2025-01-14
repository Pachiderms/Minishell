/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_rid_of_quotes(char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			len++;
	}
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != 34 && s[i] != 39)
			dest[len++] = s[i];
	}
	dest[len++] = '\0';
	return (dest);
}

char	*cut_str(char *str, char *cut)
{
	int		i;
	unsigned char *s;

	i = 0;
	s = (unsigned char *)str;
	printf("str:%s|cut:%s\n", str, cut);
	while (s[i])
	{
		if (ft_strcmp((char *)(s + i), cut) == 0)
		{
			s[i] = '\0';
			i--;
			while (ft_isspace(s[i]))
			{
				s[i] = '\0';
				i--;
			}	
			printf("s:%s|\n", s);
			return ((char *)s);
		}
		i++;
	}
	return (NULL);
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

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "echo", -1) || (!ft_strncmp(s, "cd", -1))
		|| !ft_strncmp(s, "pwd", -1) || !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1) || (!ft_strncmp(s, "env", -1) || !ft_strncmp(s, "/bin/env", -1))
		|| !ft_strncmp(s, "exit", -1))
		return (1);
	return (0);
}

int	is_cmd(char *s, char *path)
{
	int		i;
	char	*s1;
	char	*tmp;
	char	**split;

	i = 0;
	s1 = ft_strjoin("/", s);
	split = ft_split(path, ':');
	if (check_builtin(s))
			return (free(split), free(s1), 1);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, R_OK) == 0)
		{
			return (free(tmp), free(split), free(s1), 1);
		}
		tmp = NULL;
		free(tmp);
		i++;
	}
	return (free(split), free(s1), 0);
}

int	is_sc(char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "|") == 0 || ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, ">>") == 0)
		return (1);
	if (ft_strchr(s, '$'))
		return (2);
	return (0);
}

char	*replace_dollar(char *s, t_main *main)
{
	int		i;
	int		j;
	int		l;
	char	*res;
	char	*tmp;

	i = 0;
	res = 0;
	while (s[i])
	{
		j = i;
		while (s[j] && s[j] != '$')
			j++;
		if (j != i)
		{
			tmp = ft_substr(s, i, j - i);
			res = ft_strjoin(res, tmp);
			free(tmp);
			tmp = NULL;
			// printf("i=%d\tj=%d\n", i, j);
		}
		i = j;
		// printf("res before $: %s\n" ,res);
		if (s[i] == '$')
		{
			i = j;
			while (s[j] && s[j] != '=')
				j++;
			tmp = ft_substr(s, i, j - i);
			l = check_var_exists2(main, &tmp[1]);
			// printf("index=%d\n", l);
			if (l >= 0)
				res = ft_strjoin_free(res, &ft_strchr(main->env[l], '=')[1]);
			free(tmp);
			tmp = NULL;
			// printf("res after $: %s\n" ,res);
			// printf("i=%d\tj=%d\n", i, j);
			i = j;
		}
	}
	// printf("final res: %s\n", res);
	return (res);
}

int	handle_sc(t_main *main, char **split, int i)
{
	int		sc_type;

	sc_type = is_sc(split[i]);
	if (sc_type == 1)
	{
		main->tokens[i].type = sc;
		return (1);
	}
	if (sc_type == 2)
	{
		split[i] = replace_dollar(split[i], main);
		main->tokens[i].type = argument;
		return (1);
	}
	return (0);
}


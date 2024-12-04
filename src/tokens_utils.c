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

char	*get_rid_of(char *s)
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

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "echo", -1) || !ft_strncmp(s, "cd", -1)
		|| !ft_strncmp(s, "pwd", -1) || !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1) || !ft_strncmp(s, "env", -1)
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
			return (free_split(split), free(s1), 1);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, R_OK) == 0)
		{
			return (free(tmp), free_split(split), free(s1), 1);
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (free_split(split), free(s1), 0);
}

int	is_sc(char *s)
{
	if (ft_strcmp(s, "|") == 0 || ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, ">>") == 0)
		return (1);
	if (ft_strchr(s, '$'))
		return (2);
	return (0);
}
char	*get_dollar_baby(char *s, t_main *main)
{
	char	*tmp;
	char	*tmp2;
	int		yes;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	j = i;
	while (s[j] && s[j] != '=')
		j++;
	tmp = ft_substr(s, i, j - i);
	yes = check_var_exists(main->env, main->env_len, tmp);
	if (yes != 1)
		return (free(tmp), NULL);
	// printf("i=%d\tj=%d\n", i, j);
	printf("tmp: %s\n", tmp);
	if (i == 0)
	{
		tmp2 = ft_substr(s, j, ft_strlen(s) - j);
		return (ft_strjoin(main->env[check_var_exists(main->env, main->env_len, tmp)], tmp2));
	}
	else
	{
		tmp2 = ft_substr(s, 0, i);
		return (ft_strjoin(tmp2, main->env[check_var_exists(main->env, main->env_len, tmp)]));
	}
	return (0);
}

int	handle_sc(t_main *main, char **split, int i)
{
	int		sc_type;
	char	*tmp;

	sc_type = is_sc(split[i]);
	if (sc_type == 1)
	{
		main->tokens[i].type = sc;
		return (1);
	}
	if (sc_type == 2)
	{
		tmp = get_dollar_baby(split[i], main);
		printf("tmp2: %s\n", tmp);
		exit(0);
		if (check_var_exists(main->env, main->env_len, ft_strchr(tmp, '=')) != -1)
		{
			split[i] = get_dollar_baby(split[i], main);
			main->tokens[i].type = argument;
			return (free(tmp), 1);
		}
		free(tmp);
	}
	return (0);
}
char	*ft_strendchr(char *s, char end)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	while (s[len] && s[len] != end)
		len++;
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (0);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

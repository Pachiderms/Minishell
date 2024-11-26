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

char	*get_rid_of(char *s, char supr)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != supr)
		len++;
	}
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != supr)
		dest[len++] = s[i];
	}
	dest[len++] = '\0';
	return (dest);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
}

int	ft_quote(char **s, char **split, int q)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (split[i])
	{
		tmp = get_rid_of(split[i], q);
		if (ft_strchr(split[i], q))
		{
			*s = tmp;
			break ;
		}
		*s = ft_strjoin(tmp, " ");
		i++;
	}
	return (i + 1);
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
	if (ft_strcmp(s, "|") == 0 || ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, ">>") == 0)
		return (1);
	if (s[0] == '$')
		return (2);
	return (0);
}

int	handle_sc(t_main *main, char **split, int i)
{
	int		sc_type;
	char	*tmp;
	char	*tmp2;

	sc_type = is_sc(split[i]);
	if (sc_type == 1)
	{
		main->tokens[i].type = sc;
		return (1);
	}
	if (sc_type == 2)
	{
		tmp = ft_strjoin("export ", &split[i][1]);
		tmp2 = ft_strjoin(tmp, "=");
		if (check_var_exists(main->env, main->env_len, tmp2) != -1)
		{
			split[i] = &ft_strchr(main->env[check_var_exists(main->env, main->env_len, tmp2)], '=')[1];
			main->tokens[i].type = argument;
			return (free(tmp), free(tmp2), 1);
		}
		free(tmp);
		free(tmp2);
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
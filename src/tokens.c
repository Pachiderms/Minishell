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
		if (check_var_exists(main, tmp2) != -1)
		{
			split[i] = &ft_strchr(main->env[check_var_exists(main, tmp2)], '=')[1];
			main->tokens[i].type = argument;
			return (free(tmp), free(tmp2), 1);
		}
		free(tmp);
		free(tmp2);
	}
	return (0);
}

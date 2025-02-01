/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/01/31 15:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *_s)
{
	char	*s;

	s = get_cmd(_s);
	if (!ft_strncmp(s, "echo", -1) || (!ft_strncmp(s, "cd", -1)  || !ft_strncmp(s, "/bin/cd", -1))
		|| !ft_strncmp(s, "pwd", -1) || !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1)
		|| (!ft_strncmp(s, "env", -1) || !ft_strncmp(s, "/bin/env", -1))
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
	tmp = NULL;
	s1 = ft_strjoin("/", get_cmd(s));
	split = ft_split(path, ':');
	if (check_builtin(s))
		return (free_split(split), free(s1), 1);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], s1);
		if (access(tmp, R_OK) == 0)
			return (free(tmp), free_split(split), free(s1), 1);
		free(tmp);
		i++;
	}
	return (free_split(split), free(s1), 0);
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

int	check_open_quotes(char const *s, t_main *main)
{
	int i;
	int s_qts;
	int d_qts;
	int tmp = 0;
	int tmp2 = 0;
	int r = 0;
	int r1 = 0;
	i = 0;
	s_qts = 0;
	d_qts = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (s[i] == '\'')
			{
				//printf("s_qts on 1 -> s[i] : %c | i : %d\n", s[i], i);
				s_qts = 1;
				tmp = i;
				i++;
			}
			else if (s[i] == '"')
			{
				//printf("d_qts on 1 -> s[i] : %c | i : %d\n", s[i], i);
				d_qts = 1;
				tmp2 = i;
				i++;
			}
		}
		if (s_qts == 1)
		{
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] == '\'')
			{
				//printf("s_qts on 0 -> s[i] : %c | i : %d\n", s[i], i);
				s_qts = 0;
				main->s_qs[r++] = tmp;
				i++;
			}
		}
		else if (d_qts == 1)
		{
			while (s[i] != '"' && s[i])
				i++;
			if (s[i] == '"')
			{
				//printf("s_qts on 0 -> s[i] : %c | i : %d\n", s[i], i);
				d_qts = 0;
				main->d_qs[r1++] = tmp2;
				i++;
			}
		}
		//printf("s[i] : %c | i : %d\n", s[i], i);
		if (s[i] && s[i] != '\'' && s[i] != '"')
			i++;
	}
	main->s_qs[r] = -1;
	main->d_qs[r1] = -1;
	printf("s_qs0 : %d | s_qs1 : %d | s_qs2 : %d\n", main->s_qs[0], main->s_qs[1], main->s_qs[2]);
	printf("d_qs0 : %d | d_qs1 : %d | s_qs2 : %d\n", main->d_qs[0], main->d_qs[1], main->d_qs[2]);
	printf("s_qts : %d| d_qts : %d\n", s_qts, d_qts);
	if (s_qts == 1 || d_qts == 1)
		return (0);
	return (1);
}

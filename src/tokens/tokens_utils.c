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
			res = ft_strjoin_free(res, tmp, 0);
			free(tmp);
			tmp = NULL;
		}
		if (s[i + 1] && (s[i + 1] == '$' || s[i + 1] == '?'))
			return (ft_strdup(s));
		i = j;
		if (s[i] == '$')
		{
			while (s[j] && s[j] != '=')
				j++;
			tmp = ft_substr(s, i, j - i);
			l = check_var_exists2(main, &tmp[1]);
			if (l >= 0)
				res = ft_strjoin_free(res, &ft_strchr(main->env[l], '=')[1], 0);
			free(tmp);
			tmp = NULL;
			i = j;
		}
	}
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

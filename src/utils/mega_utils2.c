/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:41:20 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 20:07:38 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *cmd)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	j = 0;
	if (ft_strncmp(cmd, "export ", 7) == 0)
		i = 7;
	while (cmd[i++] != '=')
		j++;
	var_name = (char *)malloc(sizeof(char) * (j + 2));
	i = 0;
	j = 0;
	if (ft_strncmp(cmd, "export ", 7) == 0)
		i = 7;
	while (cmd[i] != '=')
	{
		var_name[j] = cmd[i];
		j++;
		i++;
	}
	var_name[j] = cmd[i];
	var_name[j + 1] = '\0';
	return (var_name);
}

int	get_dchar_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char	*add_char_to_str(char *s, char c, int _free)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = malloc((len + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i++] = c;
	res[i++] = '\0';
	if (_free)
		free(s);
	return (res);
}

int	in_quotes_skip(char *s, t_main *main, int i, char **tmp)
{
	char	*res;
	int		j;

	res = NULL;
	j = i + was_in_quotes(&s[i], main,
			ft_substr(&s[i], 0,
				ft_strlen(&s[i])));
	if (j > i)
	{
		res = ft_substr(s, i, j - i);
		*tmp = ft_strjoin_free(*tmp, res, 0);
		free(res);
		res = NULL;
	}
	return (j);
}

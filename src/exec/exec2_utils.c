/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:35 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/05 14:52:41 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_files(char *s, char r, char ns)
{
	int	i;

	i = 0;
	if (s[i] == r)
	{
		while (s[i])
		{
			if (s[i] != r && !ft_isspace(s[i]))
				break ;
			i++;
		}
		while (s[i])
		{
			if (ft_isspace(s[i]) || s[i] == ns)
				break ;
			i++;
		}
	}
	return (i);
}

int	skip_infiles(char *s, int r, int ns)
{
	int	i;

	i = 0;
	while (s[i] == '<')
		i++;
	if (!ft_strchr(&s[i], r))
		return (i);
	return (skip_files(s, r, ns));
}

char	*rm_redirections(t_cmd *token, char *cmd, int builtin)
{
	int		i;
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	i = 0;
	if (!token->args)
		return (NULL);
	while (i < (int)ft_strlen(token->args))
	{
		
		i += skip_files(&token->args[i], '>', '<');
		if (token->args[i] == '<')
			i += skip_infiles(&token->args[i], '<', '>');
		tmp = add_char_to_str(tmp, token->args[i], 1);
		i++;
	}
	if (!builtin)
		res = ft_strjoin(cmd, " ");
	if (tmp)
		res = ft_strjoin_free(res, tmp, 0);
	free(token->args);
	token->args = NULL;
	return (free(tmp), res);
}

char	*cook_cmd(char *s)
{
	if (!s)
		return (NULL);
	if (!ft_strncmp(s, "/bin/", 5))
		return (ft_strdup(s));
	else if (!ft_strncmp(s, "/usr/bin/", 9))
		return (ft_strdup(s));
	else
		return (ft_strjoin("/usr/bin/", s));
}

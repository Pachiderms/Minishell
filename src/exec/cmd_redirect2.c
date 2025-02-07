/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:53:19 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 17:00:52 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_files(char *s, char r)
{
	int		i;
	char	ns;

	if (!s)
		return (0);
	i = 0;
	ns = '<';
	if (r == '<')
		ns = '>';
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

int	skip_infiles(char *s, int r)
{
	int	i;

	i = 0;
	while (s[i] == '<')
		i++;
	if (!ft_strchr(&s[i], r))
		return (i);
	return (skip_files(s, r));
}

char	*rm_redir2(t_cmd *token, t_main *main)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < (int)ft_strlen(token->args))
	{
		i = in_quotes_skip(token->args, main, i, &tmp);
		if (i > (int)ft_strlen(token->args))
			break ;
		i += skip_files(&token->args[i], '>');
		if (token->args[i] == '<')
			i += skip_infiles(&token->args[i], '<');
		tmp = add_char_to_str(tmp, token->args[i], 1);
		i++;
	}
	return (tmp);
}

char	*rm_redirections(t_cmd *token, char *cmd, int builtin, t_main *main)
{
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	if (!token->args)
		return (NULL);
	tmp = rm_redir2(token, main);
	if (!builtin)
		res = add_char_to_str(cmd, ' ', 0);
	if (tmp)
		res = ft_strjoin_free(res, tmp, 0);
	free(token->args);
	token->args = NULL;
	return (free(tmp), res);
}

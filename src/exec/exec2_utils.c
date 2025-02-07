/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:35 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 12:07:03 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wiq2(char *s, t_main *main, int *i, int *j)
{
	if (*j > (int)ft_strlen(main->cmd_quotes))
		return (0);
	while (*j < (int)ft_strlen(main->cmd_quotes)
		&& main->cmd_quotes[*j] != main->cmd_quotes[*i])
			(*j)++;
	if (main->cmd_quotes[*j] != main->cmd_quotes[*i])
		return (0);
	if (ft_strncmp(s, &main->cmd_quotes[*i + 1],
			*j - *i - 1) == 0)
	{
		return (*j - *i);
	}
	return (0);
}

int	was_in_quotes(char *_s, t_main *main, char *base)
{
	int		i;
	int		j;
	char	*s;
	int		wq2;

	i = 0;
	j = 0;
	s = get_rid_of_quotes(_s);
	if (ft_strcmp(base, s) != 0)
	{
		free(s);
		s = ft_strdup(base);
	}
	while (i < (int)ft_strlen(main->cmd_quotes))
	{
		j = i + 1;
		if (main->cmd_quotes[i] == 34 || main->cmd_quotes[i] == 39)
		{
			wq2 = wiq2(s, main, &i, &j);
			if (wq2 > 0)
				return (free(s), free(base), wq2);
		}
		i = j;
	}
	return (free(s), free(base), 0);
}

int	skip_files(char *s, char r)
{
	int		i;
	char	ns;

	if (!s)
		return (0);
	i = 0;
	ns = r == '<' ? '>' : '<';
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

char	*rm_redirections(t_cmd *token, char *cmd, int builtin, t_main *main)
{
	int		i;
	int		j;
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	i = 0;
	if (!token->args)
		return (NULL);
	while (i < (int)ft_strlen(token->args))
	{
		j = i + was_in_quotes(&token->args[i], main,
			ft_substr(&token->args[i], 0, ft_strlen(&token->args[i])));
		if (j > i)
		{
			res = ft_substr(token->args, i, j - i - 1);
			tmp = ft_strjoin_free(tmp, res, 0);
			free(res);
			res = NULL;
		}
		i = j;
		if (i > (int)ft_strlen(token->args))
			break ;
		i += skip_files(&token->args[i], '>');
		if (token->args[i] == '<')
			i += skip_infiles(&token->args[i], '<');
		tmp = add_char_to_str(tmp, token->args[i], 1);
		i++;
	}
	if (!builtin)
		res = add_char_to_str(cmd, ' ', 0);
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
	if (!ft_strncmp(s, "./", 2))
		return (ft_strdup(s));
	if (!ft_strncmp(s, "/bin/", 5))
		return (ft_strdup(s));
	else if (!ft_strncmp(s, "/usr/bin/", 9))
		return (ft_strdup(s));
	else
		return (ft_strjoin("/usr/bin/", s));
}

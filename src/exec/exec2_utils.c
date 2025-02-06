/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:35 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/06 13:58:01 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wiq2(char *s, t_main *main, int *i, int *j)
{
	if (*j > (int)ft_strlen(main->cmd_quotes))
		return (0) ;
	while (*j < (int)ft_strlen(main->cmd_quotes)
		&& main->cmd_quotes[*j] != main->cmd_quotes[*i])
			(*j)++;
	if (*j + 1 > (int)ft_strlen(main->cmd_quotes))
		return (0) ;
	if (main->cmd_quotes[*j] != main->cmd_quotes[*i])
		return (0) ;
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
		s = ft_strdup(_s);
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

int	skip_files(char *s, char r, char **res, t_main *main)
{
	int		i;
	char	ns;

	if (!s)
		return (0);
	i = was_in_quotes(s, main, ft_substr(s, 0, ft_strlen(s)));
	if (i > 0)
	{
		*res = ft_strjoin_free(*res, s, 0);
		return (ft_strlen(s));
	}
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

int	skip_infiles(char *s, int r, char **res, t_main *main)
{
	int	i;

	if (!s)
		return (0);
	i = was_in_quotes(s, main, ft_substr(s, 0, ft_strlen(s)));
	if (i > 0)
	{
		*res = ft_strjoin_free(*res, s, 0);
		return (ft_strlen(s));
	}
	if (s[0] != '<')
		return (0);
	while (s[i] == '<')
		i++;
	if (!ft_strchr(&s[i], r))
		return (i);
	return (0);
}

char	*rm_redirections(t_cmd *token, char *cmd, int builtin, t_main *main)
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
		i += skip_files(&token->args[i], '>', &tmp, main);
		i += skip_infiles(&token->args[i], '<', &tmp, main);
		i += skip_files(&token->args[i], '<', &tmp, main);
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

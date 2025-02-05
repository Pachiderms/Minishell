/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:35 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/05 19:04:29 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	was_in_quotes(char *s, t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (main->cmd_quotes[i])
	{
		if (main->cmd_quotes[i] == 34 || main->cmd_quotes[i] == 39)
		{
			i++;
			if (i + 1 > (int)ft_strlen(main->cmd_quotes))
				break ;
			if (ft_strncmp(s, &main->cmd_quotes[i],
					ft_strlen(s)) == 0)
			{
				j = i;
				while (main->cmd_quotes[j]
					&& main->cmd_quotes[j] != main->cmd_quotes[i - 1])
						j++;
				printf("found '%s'\nwait= '%s'\n",
					ft_substr(main->cmd_quotes, i, j - i), s);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	skip_files(char *s, char r, char ns, t_main *main)
{
	int	i;

	if (!s)
		return (0);
	if (was_in_quotes(s, main))
		return (0);
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

int	skip_infiles(char *s, int r, int ns, t_main *main)
{
	int	i;

	if (!s)
		return (0);
	if (was_in_quotes(s, main))
		return (0);
	i = 0;
	if (s[0] != '<')
		return (0);
	while (s[i] == '<')
		i++;
	if (!ft_strchr(&s[i], r))
		return (i);
	return (skip_files(s, r, ns, main));
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
		printf("arg[%d] %s\n", i, &token->args[i]);
		i += skip_files(&token->args[i], '>', '<', main);
		i += skip_infiles(&token->args[i], '<', '>', main);
		printf("i skip %d\n", i);
		tmp = add_char_to_str(tmp, token->args[i], 1);
		printf("tmp %s\n", tmp);
		i++;
	}
	if (!builtin)
		res = ft_strjoin(cmd, " ");
	if (tmp)
		res = ft_strjoin_free(res, tmp, 0);
	free(token->args);
	token->args = NULL;
	printf("rm redir res %s\n", res);
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

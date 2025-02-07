/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mega_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:01:27 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 16:31:34 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_next(char **cmd, char *tf)
{
	if (!cmd)
		return (NULL);
	if (!*cmd)
		return (NULL);
	if (ft_strcmp(*cmd, tf) == 0)
	{
		if (*(cmd + 1))
			return (*(cmd + 1));
	}
	else if (ft_strnstr(*cmd, tf, ft_strlen(*cmd)))
		return (&ft_strrchr(*cmd, tf[0])[1]);
	return (NULL);
}

void	update_gpid(t_main *main)
{
	if (!ft_strcmp(main->cmd_tokens->cmd, "cat")
		|| !ft_strcmp(main->cmd_tokens->cmd, "/bin/cat")
		|| !ft_strcmp(main->cmd_tokens->cmd, "/bin/sleep")
		|| !ft_strcmp(main->cmd_tokens->cmd, "sleep")
		|| !ft_strcmp(main->cmd_tokens->cmd, "grep")
		|| !ft_strcmp(main->cmd_tokens->cmd, "/bin/grep"))
		g_signal_pid = 1;
}

int	u_ttoken(t_main *main)
{
	if (main->last_ofile)
		unlink(main->last_ofile);
	return (ft_error("serr", main->u_token));
}

int	skip_char(char *s, int c, int diff)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!diff)
	{
		while (s[i])
		{
			if (s[i] != c)
				break ;
			i++;
		}
	}
	else
	{
		while (s[i])
		{
			if (s[i] == c)
				break ;
			i++;
		}
	}
	return (i);
}

char	*handle_sc_c(char *arg, t_main *main)
{
	char	*arg_without_quotes;

	arg_without_quotes = NULL;
	if (arg == NULL)
		return (NULL);
	if (main->s_qs[0] == -1 || main->d_qs[0] == -1)
	{
		if (ft_strcmp(arg, "!") == 0 || ft_strcmp(arg, ":") == 0)
			return (free(arg), ft_strdup(""));
	}
	if (main->s_qs[0] > -1 || main->d_qs[0] > -1)
	{
		arg_without_quotes = get_rid_of_quotes(arg);
		if (ft_strcmp(arg_without_quotes, ":") == 0)
			return (free(arg_without_quotes), ft_strdup(""));
		free(arg_without_quotes);
	}
	return (arg);
}

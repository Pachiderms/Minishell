/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:35 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 15:54:57 by tzizi            ###   ########.fr       */
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

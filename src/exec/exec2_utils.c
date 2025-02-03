/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:36:35 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/03 18:41:21 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int skip_files(char *s, char r, char ns)
{
    int i;

    i = 0;
    if (s[i] == r)
    {
        while(s[i])
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

int skip_infiles(char *s, int r, int ns)
{
    int i;

    i = 0;
    while (s[i] == '<')
        i++;
    if (!ft_strchr(&s[i], r))
        return (i);
    return (skip_files(s, r, ns));
}

char    *rm_redirections(char *s, char *cmd)
{
    int     i;
    char    *tmp;
    char    *res;

    tmp = NULL;
    i = 0;
    if (!s)
        return (NULL);
    while (i < (int)ft_strlen(s))
    {
        i += skip_files(&s[i], '>', '<');
        if (s[i] == '<')
        {
            i += skip_infiles(&s[i], '<', '>');
            printf("i < %d\n", i);
        }
        tmp = add_char_to_str(tmp, s[i], 1);
        i++;
    }
    res = ft_strjoin(cmd, " ");
    res = ft_strjoin_free(res, tmp, 0);
    return (free(tmp), get_rid_of_spaces(res));
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

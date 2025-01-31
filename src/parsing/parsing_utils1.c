/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/31 12:46:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *add_char_to_str(char *s, char c, int _free)
{
        char    *res;
        int             len;
        int             i;

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

char    *cmd_separate(char *s)
{
        char    *res;
        int             i;

        i = 0;
        res = NULL;
        while (s[i])
        {
                if (s[i + 1] == '>' || s[i + 1] == '|')
                {
                        if (!ft_isspace(s[i]))
                                res = add_char_to_str(res, s[i], 1);
                        res = add_char_to_str(res, ' ', 1);
                        i++;
                }
                res = add_char_to_str(res, s[i], 1);
                i++;
        }
        return (res);
}

// placer les < au bon endoroit
char    *order(char *_s)
{
        char    *s;

        s = get_rid_of_spaces(_s);
        return (cmd_separate(s));
}

int     sizeup_no_space(char const *s) // trop de lignes
{
        size_t  i;
        int             size;

        i = 0;
        size = 0;
        while (ft_isspace(s[i]) == 1)
                i++;
        while (i < ft_strlen(s))
        {
                if (ft_isspace(s[i]) == 1)
                {
                        while (ft_isspace(s[i]) == 1)
                                i++;
                        if (s[i])
                                size++;
                }
                if (s[i] == 34 || s[i] == 39)
                {
                        i++;
                        size++;
                        while (s[i] && (s[i] != 34 && s[i] != 39))
                        {
                                size++;
                                i++;
                        }
                        if (s[i] == 34 || s[i] == 39)
                                size++;
                }
                else
                        size++;
                i++;
        }
        return (size);
}

char    *get_rid_of_spaces(char const *s) // trop de lignes
{
        int             i;
        int             j;
        int             size;
        char    *no_space;

        i = 0;
        if (!s)
                return (NULL);
        size = sizeup_no_space(s);
        no_space = malloc(sizeof(char) * size + 1);
        if (!no_space)
                return (NULL);
        i = 0;
        j = 0;
        while (ft_isspace(s[i]) == 1)
                i++;
        while (j < size)
        {
                if (ft_isspace(s[i]) == 1)
                {
                        while (ft_isspace(s[i]) == 1)
                                i++;
                        if (s[i])
                                no_space[j++] = ' ';
                }
                if (s[i] == 34 || s[i] == 39)
                {
                        no_space[j++] = s[i];
                        i++;
                        while (s[i] && (s[i] != 34 && s[i] != 39))
                        {
                                no_space[j++] = s[i];
                                i++;
                        }
                        if (s[i] == 34 || s[i] == 39)
                                no_space[j++] = s[i];
                }
                else
                        no_space[j++] = s[i];
                i++;
        }
        no_space[j] = '\0';
        return (no_space);
}

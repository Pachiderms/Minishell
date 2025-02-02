/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:15 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/02 15:22:03 by zamgar           ###   ########.fr       */
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
                if ((s[i] == '>' || s[i] == '|')
                        && s[i + 1] != s[i])
                        res = add_char_to_str(res, ' ', 1);
                i++;
        }
        return (free(s), res);
}

t_cmd   *init_cmd_tokens(char **pipes, t_main *main)
{
        char    **pipe;
        t_cmd   *cmd_tokens;
        t_cmd   *tmp;
        int     i;

        pipe = ft_split(pipes[0], ' ');
        cmd_tokens = ft_lstnew(get_fd_in(pipe), get_fd_out(pipe)
                        , find_heredoc_eof(pipe), find_cmd(pipe, main), find_args(pipe, main));
        if (cmd_tokens->cmd)
                main->nb_cmd++;
        free_split(pipe);
        i = 1;
        while (i < get_dchar_len(pipes))
        {
                pipe = ft_split(pipes[i], ' ');
                tmp = ft_lstnew(get_fd_in(pipe), get_fd_out(pipe)
                        , find_heredoc_eof(pipe), find_cmd(pipe, main), find_args(pipe, main));
                if (tmp->cmd)
                        main->nb_cmd++;
                ft_lstadd_back(&cmd_tokens, tmp);
                tmp = tmp->next;
                free_split(pipe);
                i++;
        }
        return (cmd_tokens);
}

int     order(char *_s, t_main *main)
{
        char    *s;
        char    **pipes;

        (void)main;
        s = cmd_separate(get_rid_of_spaces(_s)); // placer les ' ' manquants/supr ceux en trop
        if (check_open_quotes(s, main) == 0)
	        return (0);
        s = replace_dollar(s, main);
        s = handle_sc_c(s, main);
        s = get_rid_of_quotes(s);
        printf("order 0 '%s'\n", s);
        if (!s || s[0] == '\0')
                return (0);
        pipes = ft_split(s, '|'); // separer les pipes
        for (int i=0;pipes[i];i++)
                printf("pipe %d '%s'\n", i, pipes[i]);
        main->cmd_tokens = init_cmd_tokens(pipes, main); // initialisation tokens
        print_t_cmd(main->cmd_tokens);
        return (free(s), free_split(pipes), 1);
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

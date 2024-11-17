/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:19:24 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/12 16:19:24 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

enum e_type {command, argument, sc, end};

typedef struct token_t
{
	enum e_type	type;
	char		*value;
}	t_token;

int	is_cmd(char *s, char *path);
int	is_sc(char *s);
int	ft_findmltpchar(char *s1, char *s2);
int	check_builtin(char *s);

//utils
char    *get_rid_of(char *s, char supr);
char    **ft_double_array_clean(char **split);
void    ft_free_split(char **split);

#endif

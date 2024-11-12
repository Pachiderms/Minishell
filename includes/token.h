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

enum e_type {command, argument, sc};

typedef struct token_t
{
	enum e_type	type;
	char		*value;
}	t_token;

int	is_cmd(char *s, char *path);
int	is_sc(char *s);
int	ft_findmltpchar(char *s1, char *s2);

#endif

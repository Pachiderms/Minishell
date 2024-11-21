/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:24:04 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/21 15:24:46 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

enum e_type {command, argument, sc, end};

typedef struct token_t
{
	enum e_type	type;
	char		*value;
}	t_token;

/// Tokens
int		init_tokens(char **split, t_main *main);
int		is_cmd(char *s, char *path);
int		is_sc(char *s);
int		ft_findmltpchar(char *s1, char *s2);
int		check_builtin(char *s);
char	*get_rid_of(char *s, char supr);
/// Utils Tokens
int		ft_quote(char **s, char **split, int q);
char	**clean_split(char **split);
int	    handle_sc(t_main *main, char **split, int i);

#endif
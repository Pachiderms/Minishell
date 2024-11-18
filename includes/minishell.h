/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:25 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 20:45:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define _X_OPEN_SOURCE 700 faudra m'expliquer à quoi ça sert juste

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define GREY 	"\033[0;90m"
# define RESET	"\033[0m"

enum e_type {command, argument, sc, end};

typedef struct token_t
{
	enum e_type	type;
	char		*value;
}	t_token;

typedef struct s_main {
    char **env;
    int env_len;
    t_token	*tokens;
    int tokens_len;
    char *path;
}   t_main;

// LIBFT
size_t	ft_atoi(const char *str);
int		ft_isspace(int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

// MINISHELL
/// Env
int     init_env(char **env, t_main *main);
void    update_env(t_main *main, char *cmd, int update_type);
void    print_env(t_main *main);
/// Unset
void    unset(t_main *main, char *cmd);
int     check_syntax_unset(char *cmd);
/// Export
void    export(t_main *main, char *cmd);
int     check_syntax_export(t_main *main, char *cmd);
void    print_ascii_order(t_main *main);
/// Echo
void    ft_echo(char **cmd);
int get_fd(char **cmd);
/// Utils BuiltIns
int     check_var_exists(t_main *main, char *cmd);
void    free_old_env(char **tab, int tablen);
void    free_all_data(t_main *main);

/// Tokens
int     init_tokens(char **split, t_main *main);
int	    is_cmd(char *s, char *path);
int	    is_sc(char *s);
int	    ft_findmltpchar(char *s1, char *s2);
int	    check_builtin(char *s);
char    *get_rid_of(char *s, char supr);
/// Utils Tokens
int	    ft_quote(char **s, char **split, int q);
char	**clean_split(char **split);

//EXEC
void    ft_exec(t_main *main, char **split, char *cmd);

#endif
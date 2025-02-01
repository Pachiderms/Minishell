/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:25 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/01 13:04:30 by marvin           ###   ########.fr       */
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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define GREY 	"\033[0;90m"
# define RESET	"\033[0m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

enum e_type {command, argument, sc};

// extern pid_t	g_signal_pid;

#ifdef DEFINE_I
int cat = 0;
#else
extern int cat;
#endif

typedef struct s_dollar
{
    int i;
	int j;
	int end;
	int r;
	int r1;
	int rep_pos;
	int check;
	char *arg_dup;
	char *tmp;
	char *tmp2;
	char *tmp3;
	char *final_tmp;
}  t_dollar;

typedef struct token_t
{
	enum e_type	type;
	char		*value;
}	t_token;

typedef struct s_main {
    char	**env;
    int		env_len;
    char	**export;
    int		export_len;
    t_token	*tokens;
    t_dollar dollars;
    int		tokens_len;
    int     split_len;
    int		nb_cmd;
    char	*path;
    int     hc_pos;
    int     last_exit_code;
    char    *cmd;
    int     infile;
    int     outfile;
    int     pip[2];
    char    **split;
    char    **base_split;
    int     s_qs[42];
    int     d_qs[42];
    int ut_nl_err;
    int ut_err;
    char ut_err_c[2];
}	t_main;

// LIBFT
size_t	ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isspace(int c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char const *s1, char const *s2, int last);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int	    ft_isdigit(int c);
void	ft_putnbr_fd(int n, int fd);
char    *ft_itoa(int n);

// MINISHELL

//HERE_DOC
int     her_doc(t_main *main, char **split);

/// ENV
int		init_env(char **env, t_main *main);
int     check_syntax_env(char **split);
int	    print_env(t_main *main, int check, char **split);
/// UNSET
void	unset_env(t_main *main, char *cmd);
void	unset_export(t_main *main, char *cmd);
void	unset(t_main *main, char *cmd);
int		check_syntax_unset(char *cmd);
int	    prep_unset(t_main *main, char **split);
/// EXPORT
void    export(t_main *main, char *cmd);
int		check_syntax_export(char *cmd);
void	fill_export(t_main *main, char *cmd);
void	fill_env_export(t_main *main, char *cmd);
void	print_ascii_order(t_main *main);
int	    prep_export(t_main *main, char **split);
char	*get_var_name(char *cmd);
int     check_plus(char *cmd);
char    *get_without_plus(char *cmd);
char    *get_plus_str(t_main *main, char *cmd);
void	remake_env_fill(char **tmp, t_main *main, int which);
/// ECHO
int     ft_echo(t_main *main, char **cmd);
int		get_fd_in(char **cmd);
int		get_fd_out(char **cmd);
/// CD
int	is_special_case(char *actual_arg);
char	*get_actual_arg(t_main *main, char *arg);
int		cd(t_main *main, char **cmd);
/// PWD
int     return_to_pwd(t_main *main);
void    update_oldpwd_pwd(t_main *main);
int     pwd(t_main *main, char **cmd);
/// UTILS BUILTINS
int     basic_verif(char *arg, int which);
int		check_var_exists(char **env, int len, char *cmd);
void	remake_env(char	**tmp, t_main *main, int which, int replace_pos);
/// UTILS
int		only_space_line(char *cmd);
int     get_cmd_number(t_main *main, char **split);
char	**ft_split_k_q_s(t_main *main, char const *s, char c);
int	    closed_quotes(const char *s);
char    *get_rid_of_spaces(char const *s);
char	*order(char *s);
char    *cut_str(char *str, char *cut);

/// TOKENS
int		init_tokens(char **split, t_main *main);
int		is_cmd(char *s, char *path);
int		is_sc(char *s);
int		ft_findmltpchar(char *s1, char *s2);
int		check_builtin(char *s);
char	*get_rid_of_quotes(char *s);
char     *get_rid_of(char *s, char c);
char	*replace_dollar(char *arg, t_main *main);

/// UTILS TOKENS
int		ft_quote(char **s, char **split);
char	**clean_split(t_main *main, char **split);
int	    handle_sc(t_main *main, char **split, int i);
char	*get_cmd(char *path);
/// EXEC
int	    ft_process(t_main *main, char *cmd);
int	    builtin(t_main *main, char **split, char *cmd);
/// PIPEX
char    **prep_cmd_exec(t_main *main);
int     launch_process(t_main *main);

/// FREE
void	free_all_data(t_main *main);
void	free_process(t_main *main, int exit_code);
void	free_env(char **tab, int tablen);
void	free_tokens(t_main *main);
void    free_end_cmd(t_main *main);
void    free_split(char **split);

/// SIGNALS
void    sigint(int sig);
void    sigquit(int sig);
void    init_signals();

/// OTHERS
char	*ft_strendchr(char *s, char end);
int	    check_var_exists2(t_main *main, char *arg);
char	*ft_strchrb(const char *s, int c);
char	*get_var_name(char *cmd);
char	*handle_sc_c(char *arg, t_main *main);

#endif
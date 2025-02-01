/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:25 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/01 17:58:49 by marvin           ###   ########.fr       */
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

enum e_type {command, argument, sc};

// extern pid_t	g_signal_pid;

#ifdef DEFINE_I
int cat = 0;
#else
extern int cat;
#endif

typedef struct s_cmd
{
    char    *cmd;
    char    *args;
    int     hd;
    char    *heredoc_eof;
    int     infile;
    int     outfile;
    int     pip[2];
    struct s_cmd *next;
    
}   t_cmd;

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

typedef struct s_main {
    char	**env;
    int		env_len;
    char	**export;
    int		export_len;
    t_cmd   *cmd_tokens;
    t_dollar    dollars;
    int     s_qs[42];
    int     d_qs[42];
    int     check;
    int		nb_cmd;
    char	*path;
    int     last_exit_code;
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

//NEW PARSING
int 	get_dchar_len(char **split);
int     order(char *s, t_main *main);
char	*find_cmd(char **s, t_main *main);
char	*find_args(char **s, t_main *main);
char    *find_heredoc_eof(char **s);
char	*get_next(char **cmd, char *tf);

//t_cmd utils
void    ft_lstclear(t_cmd **lst);
void    ft_lstdelone(t_cmd *lst);
void	clear_node(t_cmd *node);
int     ft_lstsize(t_cmd *lst);
t_cmd  *ft_lstnew(int infile, int outfile, char *heredoc_eof, char *cmd, char *args);
void    ft_lstadd_back(t_cmd **lst, t_cmd *new);
void    ft_lstadd_front(t_cmd **lst, t_cmd *new);
t_cmd  *ft_lstlast(t_cmd *lst);
void    print_t_cmd(t_cmd *cmd);//a supr a la fin

//HERE_DOC
int     ft_heredoc(t_cmd *token);

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
void    remake_env_fill(char **tmp, t_main *main, int which);
/// ECHO
int     ft_echo(t_main *main, char **cmd);
int		get_fd_in(char **cmd);
int		get_fd_out(char **cmd);
/// CD
int	    is_special_case(char *actual_arg);
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
int	    closed_quotes(const char *s);
char    *get_rid_of_spaces(char const *s);
char	*replace_dollar(char *arg, t_main *main);
char    *cut_str(char *str, char *cut);

/// TOKENS
int		is_cmd(char *s, char *path);
int		is_sc(char *s);
int		ft_findmltpchar(char *s1, char *s2);
int		check_builtin(char *s);
char	*get_rid_of_quotes(char *s);
char    *get_rid_of(char *s, char c);

/// UTILS TOKENS
int     check_open_quotes(char const *s, t_main *main);
int	    handle_sc(t_main *main, char **split, int i);
char	*get_cmd(char *path);
/// EXEC
int	    ft_process(t_main *main);
int	    builtin(t_main *main);
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
int	    check_var_exists2(t_main *main, char *arg);
char	*get_var_name(char *cmd);
char    *add_char_to_str(char *s, char c, int _free);
#endif
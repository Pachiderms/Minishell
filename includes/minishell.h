/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:54:25 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/21 15:27:47 by tzizi            ###   ########.fr       */
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
#include "token.h"
#include "libft.h"

# define GREEN	"\033[0;32m"
# define RED	"\033[0;31m"
# define GREY 	"\033[0;90m"
# define RESET	"\033[0m"

typedef struct s_main {
    char	**env;
    int		env_len;
    t_token	*tokens;
    int		tokens_len;
    int		nb_cmd;
    char	*path;
}	t_main;

// MINISHELL
/// Env
int		init_env(char **env, t_main *main);
void	print_env(t_main *main);
/// Unset
void	unset(t_main *main, char *cmd);
int		check_syntax_unset(char *cmd);
void	prep_unset(t_main *main, char **split);
/// Export
void	export(t_main *main, char *cmd);
int		check_syntax_export(t_main *main, char *cmd);
void	print_ascii_order(t_main *main);
void	prep_export(t_main *main, char **split);
/// Echo
void	ft_echo(char **cmd);
int		get_fd_out(char **cmd);
int		get_fd_in(char **cmd);
// Cd
void	update_oldpwd_pwd(t_main *main);
int		cd(t_main *main, char *cmd);
// Pwd
int		pwd(void);
/// Utils BuiltIns
int		check_var_exists(t_main *main, char *cmd);
void	free_old_env(char **tab, int tablen);
void	free_all_data(t_main *main);
//Utils
int		only_space_line(char *cmd);
int     get_cmd_number(t_main *main, char **split);
//EXEC
void	ft_exec(t_main *main, char **split, char *cmd);
void    ft_fork(t_main *main, char **split);
//PIPEX
void	pipex(t_main *main, char **split);
//ORGANISE
char    *prep_cmd(char *cmd);
char    *prep_cmd_excve(t_main *main, char **split);

#endif
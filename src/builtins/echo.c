/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:06:47 by tzizi             #+#    #+#             */
/*   Updated: 2024/11/18 17:06:47 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	echo_prompt(char *cmd, int nl)
// {
// 	ft_putstr_fd(cmd, 1);
// 	if (nl)
// 		ft_putstr_fd("\n", 1);
// }

// void	echo_file(char *cmd, int fd, int nl)
// {
// 	int	i;

// 	i = 1;
// 	if (!nl)
// 		i++;
// 	while (cmd[i] && !is_sc(cmd[i]))
// 	{
// 		ft_putstr_fd(cmd[i], fd);
// 		if (cmd[i + 1])
// 			ft_putstr_fd(" ", fd);
// 		i++;
// 	}
// 	if (nl)
// 		ft_putstr_fd("\n", fd);
// 	close(fd);
// }

int	echo_dollar(t_main *main, char *arg)
{
	if (ft_strlen(arg) == 1)
		ft_putchar_fd('$', 1);
	else if (ft_strchr(arg, '$')[1] == '?')
	{
		ft_putnbr_fd(main->last_exit_code, 1);
	}
	return (ft_putchar_fd('\n', 1), 0);
}

int	ft_echo(t_main *main)
{
	int		fd;
	char		*nl;

	nl = find_newline(main->cmd_tokens->args);
	printf("nl '%s'\n", nl);
	fd = main->cmd_tokens->outfile;
	if (fd == -1)
		fd = 1;
	// if (fd < 0 || !arg)
	// 	return (perror(GREY"minishell"), 1);
	// if (arg[0] == '$')
	// 	return (echo_dollar(main, ));
	// else
	// {
	// 	if (nl)
	// 		ft_putendl_fd(, fd);
	// 	else
	// 		ft_putstr_fd(, fd);
	// 	if (fd > 1)
	// 		close(fd);
	// }
	return (0);
}

int	prep_echo(t_main *main, char *args)
{
	// char	*first_word;
	// char	*to_print_fisrt;
	// char	*next_words;
	// int		words;

	// first_word = NULL;
	// next_words = NULL;
	// words = get_arg_len(args);
	// if (words <= 0)
	// 	return (1);
	// get_arg_solo(args, &first_word, 0);
	// get_arg_solo(args, &to_print_fisrt, 1);
	// next_words = get_rid_of_spaces(ft_strnstr(args, first_word, ft_strlen(args)));
	// printf("fw '%s' nw '%s'\n", first_word, next_words);
	// ft_echo(main, first_word, to_print_fisrt);
	// return (ft_echo(main, next_words, next_words));
	(void)main;
	(void)args;
	return (0);
}

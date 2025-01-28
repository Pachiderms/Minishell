/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:19 by tzizi             #+#    #+#             */
/*   Updated: 2024/12/23 14:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint(int sig)
{
	(void)sig;
	printf("\n");
	//printf("cat signal : %d\n", cat);
	if (cat == 0)
		rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	sigquit(int sig)
{
	(void)sig;
	if (cat == 1)
		printf("Quit (core dumped)\n");
	if (cat == 0)
		rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\033[K");
	return ;
}

void	sigtstp(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\033[K");
	return ;
}

void	init_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	signal(SIGTSTP, sigtstp);
	return ;
}

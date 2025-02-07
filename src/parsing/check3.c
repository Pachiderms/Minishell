/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <zamgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:07:16 by tzizi             #+#    #+#             */
/*   Updated: 2025/02/07 18:15:33 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_double_redirection(char *arg, t_main *main, int i, int *j)
{
	*j = i + skip_char(&arg[i + 2], ' ', 0) + 2;
	if (i != *j)
	{
		if (ft_strncmp(&arg[*j], "<<", 2) == 0)
			main->u_token = "<<";
		else if (ft_strncmp(&arg[*j], ">>", 2) == 0)
			main->u_token = ">>";
		else if (ft_strncmp(&arg[*j], "<>", 2) == 0)
			main->u_token = "<>";
		else if (ft_strncmp(&arg[*j], "><", 2) == 0)
			main->u_token = "><";
		else if (ft_strncmp(&arg[*j], "<", 1) == 0)
			main->u_token = "<";
		else if (ft_strncmp(&arg[*j], ">", 1) == 0)
			main->u_token = ">";
	}
	if (arg[i + 2] == '\0')
		main->u_token = "newline";
	else if (arg[i + 2] == arg[i])
	{
		if (arg[i] == '>')
			main->u_token = ">>";
		else if (arg[i] == '<')
			main->u_token = "<<";
	}
}

void	do_double_pipe(char *arg, t_main *main, int i, int *j)
{
	*j = i + skip_char(&arg[i + 2], ' ', 0) + 2;
	if (i != *j)
	{
		if (ft_strncmp(&arg[*j], "||", 2) == 0)
			main->u_token = "||";
	}
	if (arg[i + 2] == '\0' || arg[i + 2] == arg[i])
		main->u_token = "||";
}

void	do_single_redirection(char *arg, t_main *main, int i, int *j)
{
	*j = i + skip_char(&arg[i + 1], ' ', 0) + 1;
	if (i != *j)
	{
		if (ft_strncmp(&arg[*j], "<<", 2) == 0)
			main->u_token = "<<";
		else if (ft_strncmp(&arg[*j], ">>", 2) == 0)
			main->u_token = ">>";
		else if (ft_strncmp(&arg[*j], "<>", 2) == 0)
			main->u_token = "<>";
		else if (ft_strncmp(&arg[*j], "><", 2) == 0)
			main->u_token = "><";
		else if (ft_strncmp(&arg[*j], "<", 1) == 0)
			main->u_token = "<";
		else if (ft_strncmp(&arg[*j], ">", 1) == 0)
			main->u_token = ">";
	}
	if (arg[i + 1] == '\0' || arg[i + 1] == '|')
		main->u_token = "newline";
}

int	check_global_syntax_pipe(char *arg, t_main *main)
{
	int	i;
	int	j;

	i = 0;
	if (!arg)
		return (1);
	while (i < (int)ft_strlen(arg))
	{
		i += was_in_quotes(&arg[i], main,
				ft_substr(&arg[i], 0, ft_strlen(&arg[i])));
		if (i > (int)ft_strlen(arg))
			break ;
		if (ft_strncmp(&arg[i], "||", 2) == 0)
			do_double_pipe(arg, main, i, &j);
		else if (ft_strncmp(&arg[i], "|", 1) == 0)
			do_single_pipe(arg, main, i, &j);
		if (main->u_token)
			break ;
		i++;
	}
	return (main->u_token == NULL);
}

void	do_single_pipe(char *arg, t_main *main, int i, int *j)
{
	*j = i + skip_char(&arg[i + 1], ' ', 0) + 1;
	if (i != *j)
	{
		if (ft_strncmp(&arg[*j], "|", 2) == 0)
			main->u_token = "|";
	}
	if (arg[i + 1] == '\0')
		main->u_token = "|";
}

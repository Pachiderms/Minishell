/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:12:34 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/04 19:22:02 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	calc_index(char *eof, t_main *main)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (main->cmd_quotes[i])
	{
		if (main->cmd_quotes[i] == eof[0])
		{
			index = i;
			if (ft_strncmp(&main->cmd_quotes[i], "hola", 4) == 0)
				return (index);
		}
		i++;
	}
	return (-1);
}

int	quotes_found(char *eof, t_main *main)
{
	int	index;
	int	end_eof;

	index = calc_index(eof, main);
	end_eof = 0;
	while (eof[end_eof])
		end_eof++;
	printf("main->cmd_quotes : %s\n", main->cmd_quotes);
	printf("main->cmd_quotes[index] : '%c' | main->cmd_quotes[index + end_eof] : %c\n", main->cmd_quotes[index], main->cmd_quotes[index + end_eof - 1]);
	while (main->cmd_quotes[index] != main->cmd_quotes[index + end_eof])
	{
		if (in_dquote(main, main->cmd_quotes, index) == 1
			|| in_squote(main, main->cmd_quotes, index) == 1)
			return (1);
		index++;
	}
	return (0);
}

int	write_in_here_doc(int here_doc, char *eof, t_main *main)
{
	char	*tmp;
	char	*res;

	res = NULL;
	while (1)
	{
		tmp = NULL;
		tmp = readline("heredoc> ");
		if (!tmp)
			return (free(res), 0);
		if (!ft_strcmp(eof, tmp))
			break ;
		if (ft_strchr(tmp, '$') && !quotes_found(eof, main))
			tmp = replace_dollar(tmp, main);
		res = ft_strjoin_free(res, tmp, 0);
		res = ft_strjoin_free(res, "\n", 0);
		add_history(tmp);
		free(tmp);
	}
	free(tmp);
	ft_putstr_fd(res, here_doc);
	return (free(res), 1);
}

int	ft_heredoc(t_cmd *token, int builtin, t_main *main)
{
	int	here_doc;

	if (!token->heredoc_eof)
		return (token->infile);
	here_doc = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (here_doc < 0)
		return (-1);
	if (!write_in_here_doc(here_doc, token->heredoc_eof, main))
	{
		unlink("heredoc.tmp");
		return (token->infile);
	}
	else if (!builtin)
	{
		token->args = ft_strjoin_free(token->args, " heredoc.tmp", 0);
	}
	return (here_doc);
}

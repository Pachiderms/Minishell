/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:10:51 by zamgar            #+#    #+#             */
/*   Updated: 2025/02/06 13:14:02 by tzizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_main *main)
{
	int				i;
	unsigned char	returned_value;
	char			*cmd;
	char			**split_exit;

	i = 0;
	returned_value = 0;
	cmd = main->cmd_tokens->args;
	split_exit = ft_split(cmd, ' ');
	while (i < (int)ft_strlen(split_exit[1]))
	{
		if (ft_isalpha(split_exit[1][i]))
			return (printf("minishell: exit: %s: numeric argument required\n",
					split_exit[1]), free_split(split_exit), 2);
		i++;
	}
	if (3 <= get_dchar_len(split_exit))
		return (printf("minishell: exit: too many arguments\n"),
			free_split(split_exit), -1);
	returned_value = ft_atoi(split_exit[1]);
	return (free_split(split_exit), returned_value);
}

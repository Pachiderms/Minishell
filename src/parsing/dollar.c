/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:02 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 15:57:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_replace(char **arg_dup, char *final_tmp)
{
	//printf("arg : %s | final_tmp : %s\n", *arg_dup, final_tmp);
	free(*arg_dup);
	*arg_dup = NULL;
	*arg_dup = ft_strdup(final_tmp);
}

void	begin_things(t_main *main, char *arg)
{
	main->dollars.arg_dup = ft_strdup(arg);
	free(arg);
	if (main->dollars.final_tmp)
		main->dollars.final_tmp = NULL;
}

void	end_things(t_main *main)
{
	main->dollars.i = 0;
	free(main->dollars.arg_dup);
	main->dollars.arg_dup = NULL;
	if (ft_strchr(main->dollars.final_tmp, '\\'))
		del_backslash(&main->dollars.final_tmp);
}

void	update_index(t_main *main)
{
	main->dollars.i = main->dollars.j;
	if (main->dollars.arg_dup[main->dollars.i] == '$')
		main->dollars.i += 1;
}

char	*replace_dollar(char *arg, t_main *main)
{
	begin_things(main, arg);
	while (main->dollars.arg_dup[main->dollars.i])
	{
		if (begin_verif(main->dollars.arg_dup[main->dollars.j],
				main->dollars.arg_dup[main->dollars.j + 1], main) == 1)
			main->dollars.j++;
		while (main->dollars.arg_dup[main->dollars.j] != '$'
			&& main->dollars.arg_dup[main->dollars.j])
			search_sollar(main, main->dollars.arg_dup);
		if (main->dollars.j > 0)
			main->dollars.tmp = ft_substr(main->dollars.arg_dup,
					main->dollars.i, (main->dollars.j - main->dollars.i));
		update_index(main);
		while (!big_while(main->dollars.arg_dup[main->dollars.i], 0))
			main->dollars.i++;
		if ((size_t)main->dollars.i != ft_strlen(main->dollars.arg_dup))
			main->dollars.tmp3 = create_end_str(main, main->dollars.arg_dup);
		else
			main->dollars.end = ft_strlen(main->dollars.arg_dup);
		create_and_replace_tmp2(main);
		main->dollars.final_tmp = attach_tmps(main->dollars.tmp,
				main->dollars.tmp2, main->dollars.tmp3);
		clear_dollar(main);
	}
	return (end_things(main), main->dollars.final_tmp);
}

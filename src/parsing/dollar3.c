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

void	replace_minus2(t_main *main, char **tmp2)
{
	int		diff;
	char	*tmp;

	tmp = ft_itoa(main->last_exit_code);
	diff = ft_strlen(tmp) - 2;
	free(tmp);
	update_sq_pos(main, main->dollars.r, main->dollars.r1, diff);
	free(*(tmp2));
	*(tmp2) = NULL;
}

void	replace_existing(t_main *main, char **tmp2)
{
	int	diff;

	diff = ft_strlen(&ft_strchr(main->env[main->dollars.rep_pos],
				'=')[1]) - ft_strlen(*(tmp2));
	update_sq_pos(main, main->dollars.r, main->dollars.r1, diff);
	free(*(tmp2));
	*(tmp2) = NULL;
}

// a voir deuxieme condition
void	replace(t_main *main, char **tmp2)
{
	if (ft_strcmp (*tmp2, "$") == 0 && main->dollars.check == 0)
		return ;
	if (main->dollars.rep_pos >= 0)
	{
		replace_existing(main, tmp2);
		*tmp2 = ft_strdup(&ft_strchr(main->env[main->dollars.rep_pos], '=')[1]);
	}
	else if (main->dollars.rep_pos == -1 || main->dollars.check == 1)
	{
		update_dq_pos(main, main->dollars.r, main->dollars.r1,
			ft_strlen(*(tmp2)));
		free(*(tmp2));
		*(tmp2) = NULL;
	}
	else if (main->dollars.rep_pos == -2)
	{
		replace_minus2(main, tmp2);
		*tmp2 = ft_itoa(main->last_exit_code);
	}
	else if (main->dollars.rep_pos == -3)
	{
		free(*(tmp2));
		*(tmp2) = NULL;
		*tmp2 = ft_strdup("1000");
	}
}

char	*attach_tmps(char *tmp, char *replaced_tmp2, char *tmp3)
{
	char	*final_tmp;

	final_tmp = NULL;
	if (!tmp && !replaced_tmp2 && !tmp3)
		return (final_tmp);
	if (!tmp && !tmp3)
		final_tmp = ft_strjoin(final_tmp, replaced_tmp2);
	else if (!replaced_tmp2 && !tmp3)
		final_tmp = ft_strjoin(final_tmp, tmp);
	else if (!tmp && !replaced_tmp2)
		final_tmp = ft_strjoin(final_tmp, tmp3);
	else if (!tmp)
		final_tmp = ft_strjoin(replaced_tmp2, tmp3);
	else if (!replaced_tmp2)
		final_tmp = ft_strjoin(tmp, tmp3);
	else if (!tmp3)
		final_tmp = ft_strjoin(tmp, replaced_tmp2);
	else if (tmp && replaced_tmp2 && tmp3)
	{
		final_tmp = ft_strjoin(tmp, replaced_tmp2);
		final_tmp = ft_strjoin_free(final_tmp, tmp3, 0);
	}
	return (final_tmp);
}

int	in_squote(t_main *main, char *arg_dup, int j)
{
	int	i;
	int	r;
	int	begin;
	int	end;

	i = 0;
	r = 0;
	begin = 0;
	end = 0;
	while (main->s_qs[r] != -1)
	{
		i = main->s_qs[r];
		begin = i;
		i++;
		while (arg_dup[i] != '\'')
			i++;
		end = i;
		if (j > begin && j < end)
			return (1);
		r++;
	}
	return (0);
}

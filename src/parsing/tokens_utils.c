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

char	*cut_str(char *str, char *cut)
{
	int		i;
	unsigned char *s;

	i = 0;
	s = (unsigned char *)str;
	if (!cut || !str)
		return (str);
	while (s[i])
	{
		if (ft_strcmp((char *)(s + i), cut) == 0)
		{
			s[i] = '\0';
			i--;
			return ((char *)s);
		}
		i++;
	}
	return (NULL);
}
void	update_quotes_pos(t_main *main, int r, int r1, int diff, int which)
{
	if (which == 0)
	{
		while (main->s_qs[r] != -1)
		{
			main->s_qs[r] += diff;
			r++;
		}
		while (main->d_qs[r1] != -1)
		{
			main->d_qs[r1] += diff;
			r1++;
		}
	}
	if (which == 1)
	{
		while (main->s_qs[r] != -1)
		{
			main->s_qs[r] -= diff;
			r++;
		}
		while (main->d_qs[r1] != -1)
		{
			main->d_qs[r1] -= diff;
			r1++;
		}
	}
}

void	replace(t_main *main, char **tmp2)
{
	int diff;
	int r_b;
	int r1_b;

	diff = 0;
	r_b = main->dollars.r;
	r1_b = main->dollars.r1;
	if (ft_strcmp (*tmp2, "$") == 0 && main->dollars.check == 0)
		return ;
	if (main->dollars.rep_pos >= 0)
	{
		diff = ft_strlen(&ft_strchr(main->env[main->dollars.rep_pos], '=')[1]) - ft_strlen(*(tmp2));
		update_quotes_pos(main, r_b, r1_b, diff, 0);
		free(*(tmp2));
		*(tmp2) = NULL;
		*tmp2 = ft_strdup(&ft_strchr(main->env[main->dollars.rep_pos], '=')[1]);
	}
	else if (main->dollars.rep_pos == -1 || main->dollars.check == 1)
	{
		update_quotes_pos(main, r_b, r1_b, ft_strlen(*(tmp2)), 1);
		free(*(tmp2));
		*(tmp2) = NULL;
		*tmp2 = ft_strdup("");
	}
	else if (main->dollars.rep_pos == -2)
	{
		diff = ft_strlen(ft_itoa(main->last_exit_code)) - 2;
		update_quotes_pos(main, r_b, r1_b, diff, 0);
		free(*(tmp2));
		*(tmp2) = NULL;
		*tmp2 = ft_strdup(ft_itoa(main->last_exit_code));
	}
	else if (main->dollars.rep_pos == -3)
		*tmp2 = ft_strdup("1000");
}

char	*attach_tmps(char *tmp, char *replaced_tmp2, char *tmp3) // leaks à gérer, voir last
{
	char *final_tmp = NULL;

	if (!tmp && !replaced_tmp2 && !tmp3)
		return (final_tmp);
	if (!tmp && !tmp3)
		final_tmp = ft_strjoin_free(final_tmp, replaced_tmp2, 0);
	else if (!replaced_tmp2 && !tmp3)
		final_tmp = ft_strjoin_free(final_tmp, tmp, 0);
	else if (!tmp && !replaced_tmp2)
		final_tmp = ft_strjoin_free(final_tmp, tmp3, 0);
	else if (!tmp)
		final_tmp = ft_strjoin(replaced_tmp2, tmp3);
	else if (!replaced_tmp2)
		final_tmp = ft_strjoin(tmp, tmp3);
	else if (!tmp3)
		final_tmp = ft_strjoin(tmp, replaced_tmp2);
	return (final_tmp);
}

void	arg_replace(char **arg_dup, char *final_tmp)
{
	free(*arg_dup);
	*arg_dup = NULL;
	*arg_dup = ft_strdup(final_tmp);
}

int	in_squote(t_main *main, char *arg_dup, int j)
{
	int i = 0;
	int r = 0;
	while (main->s_qs[r] != -1)
	{
		i = main->s_qs[r];
		int begin = i;
		i++;
		while (arg_dup[i] != '\'')
			i++;
		int end = i;
		if (j > begin && j < end)
			return (1);
		r++;
	}
	return (0);
}

int	in_dquote(t_main *main, char *arg_dup, int j)
{
	int i = 0;
	int r1 = 0;
	while (main->d_qs[r1] != -1)
	{
		i = main->d_qs[r1];
		int begin = i;
		i++;
		while (arg_dup[i] != '"')
			i++;
		int end = i;
		if (j > begin && j < end)
			return (1);
		r1++;
	}
	return (0);
}

char *fill_test(char *tmp, int size)
{
	int i;
	int j;
	char *final;

	final = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] != '\\')
		{
			final[j] = tmp[i];
			j++;
		}
		i++;
	}
	final[j] = '\0';
	return (final);
}

void	del_backslash(char **final_tmp)
{
	int i;
	int bs;
	char *tmp;

	i = 0;
	bs = 0;
	tmp = ft_strdup(*(final_tmp));
	while (tmp[i])
	{
		if (tmp[i] == '\\')
			bs++;
		i++;
	}
	free(*(final_tmp));
	*(final_tmp) = NULL;
	*final_tmp = fill_test(tmp, (i - bs));
}

void	search_sollar(t_main *main, char *arg_dup)
{
	if (main->dollars.j == main->s_qs[main->dollars.r])
	{
		main->dollars.j++;
		while (arg_dup[main->dollars.j] != '\'')
			main->dollars.j++;
		main->dollars.r++;
	}
	if (main->dollars.j == main->d_qs[main->dollars.r1])
		main->dollars.r1++;
	if (arg_dup[main->dollars.j] == '\\' && arg_dup[main->dollars.j + 1] == '$')
				main->dollars.j += 2;
	main->dollars.j++;
	if (arg_dup[main->dollars.j] == '$' && (arg_dup[main->dollars.j + 1] == ' ' || arg_dup[main->dollars.j + 1] == '=' || arg_dup[main->dollars.j + 1] == ':' || ((arg_dup[main->dollars.j + 1] == '"' || arg_dup[main->dollars.j + 1] == '\'') && in_dquote(main, arg_dup, main->dollars.j) == 1)))
		main->dollars.j++;
}

char	*create_end_str(t_main *main, char *arg_dup)
{
	if (((arg_dup[main->dollars.i] == '"' && main->d_qs[main->dollars.r1] == main->dollars.i) || (arg_dup[main->dollars.i] == '\'' && main->s_qs[main->dollars.r] == main->dollars.i)) && arg_dup[main->dollars.i - 1] == '$')
		main->dollars.check = 1;
	if ((arg_dup[main->dollars.i] == '?' || (arg_dup[main->dollars.i] >= '0' && arg_dup[main->dollars.i] <= '9')) && arg_dup[main->dollars.i - 1] == '$')
		main->dollars.i += 1;
	else if ((arg_dup[main->dollars.i] >= '0' && arg_dup[main->dollars.i] <= '9') && arg_dup[main->dollars.i - 1] != '$')
	{
		while (main->dollars.arg_dup[main->dollars.i] != '$' && main->dollars.arg_dup[main->dollars.i] != '?'
			&& main->dollars.arg_dup[main->dollars.i] != '=' && (main->dollars.arg_dup[main->dollars.i] != '"')
			&& (main->dollars.arg_dup[main->dollars.i] != '\'') && main->dollars.arg_dup[main->dollars.i] != ' '
			&& main->dollars.arg_dup[main->dollars.i] != ':' && main->dollars.arg_dup[main->dollars.i] != '%'
			&& main->dollars.arg_dup[main->dollars.i] != '\\' && main->dollars.arg_dup[main->dollars.i] != ']'
			&& main->dollars.arg_dup[main->dollars.i])
			main->dollars.i++;
	}
	main->dollars.end = main->dollars.i;
	return (ft_substr(arg_dup, main->dollars.i, (ft_strlen(arg_dup) - main->dollars.i)));
}

void	clear_dollar(t_main *main)
{
	//printf("end : %d | arg_dup len : %ld\n", main->dollars.end, ft_strlen(main->dollars.arg_dup));
	if ((size_t)main->dollars.end == ft_strlen(main->dollars.arg_dup))
	{
		if (main->dollars.tmp)
		{
			free(main->dollars.tmp);
			main->dollars.tmp = NULL;
		}
		if (main->dollars.tmp3)
		{
			free(main->dollars.tmp3);
			main->dollars.tmp3 = NULL;
		}
		if (main->dollars.tmp2)
		{
			free(main->dollars.tmp2);
			main->dollars.tmp2 = NULL;
		}
		main->dollars.i = main->dollars.end;
		main->dollars.j = 0;
		main->dollars.end = 0;
		main->dollars.r = 0;
		main->dollars.r1 = 0;
		main->dollars.rep_pos = 0;
		main->dollars.check = 0;
	}
	else
	{
		//printf("\n");
		arg_replace(&main->dollars.arg_dup, main->dollars.final_tmp); // no sure
		if (main->dollars.tmp)
		{
			free(main->dollars.tmp);
			main->dollars.tmp = NULL;
		}
		if (main->dollars.tmp3)
		{
			free(main->dollars.tmp3);
			main->dollars.tmp3 = NULL;
		}
		if (main->dollars.tmp2)
		{
			free(main->dollars.tmp2);
			main->dollars.tmp2 = NULL;
		}
		free(main->dollars.final_tmp);
		main->dollars.final_tmp = NULL;
		main->dollars.i = 0;
		main->dollars.j = 0;
		main->dollars.end = 0;
		main->dollars.r = 0;
		main->dollars.r1 = 0;
		main->dollars.rep_pos = 0;
		main->dollars.check = 0;
	}
}
void	print_values(t_main *main)
{
	printf("\n");
	printf("i : %d\n", main->dollars.i);
	printf("j : %d\n", main->dollars.j);
	printf("end : %d\n", main->dollars.end);
	printf("r : %d\n", main->dollars.r);
	printf("r1 : %d\n", main->dollars.r1);
	printf("rep_pos : %d\n", main->dollars.rep_pos);
	printf("check : %d\n", main->dollars.check);
	printf("arg_dup : <%s>\n", main->dollars.arg_dup);
	printf("tmp : <%s>\n", main->dollars.tmp);
	printf("tmp2 : <%s>\n", main->dollars.tmp2);
	printf("tmp3 : <%s>\n", main->dollars.tmp3);
	printf("final_tmp : <%s>\n", main->dollars.final_tmp);
	printf("\n");
}

char	*replace_dollar(char *arg, t_main *main)
{
	main->dollars.arg_dup = ft_strdup(arg);
	free(arg);
	if (main->dollars.final_tmp)
		main->dollars.final_tmp = NULL;
	//print_values(main);
	while (main->dollars.arg_dup[main->dollars.i])
	{
		//printf("arg_dup : <%s>\n", main->dollars.arg_dup); //
		if (main->dollars.arg_dup[main->dollars.j] == '$' && (main->dollars.arg_dup[main->dollars.j + 1] == ' '
		|| main->dollars.arg_dup[main->dollars.j + 1] == '=' || main->dollars.arg_dup[main->dollars.j + 1] == ':'
		|| (main->dollars.arg_dup[main->dollars.j + 1] == '"' && in_dquote(main, main->dollars.arg_dup, main->dollars.j) == 1)))
			main->dollars.j++;
		while (main->dollars.arg_dup[main->dollars.j] != '$' && main->dollars.arg_dup[main->dollars.j])
			search_sollar(main, main->dollars.arg_dup);
		if (main->dollars.j > 0)
		{ //
			main->dollars.tmp = ft_substr(main->dollars.arg_dup, main->dollars.i, (main->dollars.j - main->dollars.i));
			//printf("tmp_debut : <%s>\n", main->dollars.tmp); //
		} //
		main->dollars.i = main->dollars.j;
		if (main->dollars.arg_dup[main->dollars.i] == '$')
			main->dollars.i += 1;
		while (main->dollars.arg_dup[main->dollars.i] != '$' && main->dollars.arg_dup[main->dollars.i] != '?'
			&& main->dollars.arg_dup[main->dollars.i] != '=' && (main->dollars.arg_dup[main->dollars.i] != '"')
			&& (main->dollars.arg_dup[main->dollars.i] != '\'') && main->dollars.arg_dup[main->dollars.i] != ' '
			&& main->dollars.arg_dup[main->dollars.i] != ':' && !ft_isdigit(main->dollars.arg_dup[main->dollars.i])
			&& main->dollars.arg_dup[main->dollars.i] != '%' && main->dollars.arg_dup[main->dollars.i] != '\\'
			&& main->dollars.arg_dup[main->dollars.i] != ']' && main->dollars.arg_dup[main->dollars.i])
			main->dollars.i++;
		if ((size_t)main->dollars.i != ft_strlen(main->dollars.arg_dup))
		{ //
			main->dollars.tmp3 = create_end_str(main, main->dollars.arg_dup);
			//printf("tmp3_end : <%s>\n", main->dollars.tmp3); //
		} //
		else
			main->dollars.end = ft_strlen(main->dollars.arg_dup);
		if (ft_strcmp(main->dollars.tmp, main->dollars.arg_dup) != 0)
		{
			main->dollars.tmp2 = ft_substr(main->dollars.arg_dup, main->dollars.j, (main->dollars.end - main->dollars.j));
			//printf("tmp2_dollar : <%s>\n", main->dollars.tmp2); //
			main->dollars.rep_pos = check_var_exists2(main, &main->dollars.tmp2[1]); // not sure
			replace(main, &main->dollars.tmp2); // not sure
		}
		//printf("\n"); //
		//printf("tmp_debut : <%s>\n", main->dollars.tmp); //
		//printf("tmp2_dollar replaced : %s\n", main->dollars.tmp2); //
		//printf("tmp3_end : <%s>\n", main->dollars.tmp3); //
		main->dollars.final_tmp = attach_tmps(main->dollars.tmp, main->dollars.tmp2, main->dollars.tmp3);
		//printf("final_tmp : <%s>\n", main->dollars.final_tmp); //
		clear_dollar(main);
	}
	main->dollars.i = 0;
	free(main->dollars.arg_dup);
	main->dollars.arg_dup = NULL;
	if (ft_strchr(main->dollars.final_tmp, '\\'))
		del_backslash(&main->dollars.final_tmp); // not sure
	//print_values(main);
	return (main->dollars.final_tmp);
}

// void	redirections_handler(char *arg, t_main *main)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = 0;
// 	while (arg[i] != '>' && arg[i] != '<')
// 		i++;
// 	if (in_dquote)
// 	{
		
// 	}

// 	else if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<<") == 0 || ft_strcmp(arg, "<>") == 0)
// 			main->ut_nl_err = 1;
// }

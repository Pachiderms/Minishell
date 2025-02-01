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

void	replace(t_main *main, char **tmp2, int rep_pos, int r, int r1, int check)
{
	int diff;

	diff = 0;
	if (ft_strcmp (*tmp2, "$") == 0 && check == 0)
		return ;
	if (rep_pos >= 0)
	{
		diff = ft_strlen(&ft_strchr(main->env[rep_pos], '=')[1]) - ft_strlen(*(tmp2));
		update_quotes_pos(main, r, r1, diff, 0);
		*tmp2 = ft_strdup(&ft_strchr(main->env[rep_pos], '=')[1]);
	}
	else if (rep_pos == -1 || check == 1)
	{
		update_quotes_pos(main, r, r1, ft_strlen(*(tmp2)), 1);
		*tmp2 = ft_strdup("");
	}
	else if (rep_pos == -2)
	{
		diff = ft_strlen(ft_itoa(main->last_exit_code)) - 2;
		update_quotes_pos(main, r, r1, diff, 0);
		*tmp2 = ft_strdup(ft_itoa(main->last_exit_code));
	}
	else if (rep_pos == -3)
		*tmp2 = ft_strdup("1000");
}

char	*attach_tmps(char *tmp, char *replaced_tmp2, char *tmp3)
{
	char *final_tmp = NULL;
	int check = 0;

	if (!tmp && !tmp3)
		final_tmp = ft_strjoin(final_tmp, replaced_tmp2);
	if (tmp)
	{
		check = 1;
		final_tmp = ft_strjoin(final_tmp, tmp);
		final_tmp = ft_strjoin(final_tmp, replaced_tmp2);
	}
	if (tmp3)
	{
		if (check == 0)
			final_tmp = ft_strjoin(final_tmp, replaced_tmp2);
		final_tmp = ft_strjoin(final_tmp, tmp3);
	}
	return (final_tmp);
}

void	arg_replace(char **arg_dup, char *final_tmp)
{
	free(*arg_dup);
	*arg_dup = NULL;
	*arg_dup = ft_strdup(final_tmp);
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
	printf("final : %s\n", *final_tmp);
}



char	*replace_dollar(char *arg, t_main *main)
{
	int i;
	int j;
	int end;
	char *tmp = NULL;
	char *tmp2 = NULL;
	char *tmp3 = NULL;
	char *final_tmp = NULL;
	char *arg_dup = NULL;
	int check = 0;

	i = 0;
	j = 0;
	end = 0;
	int r = 0;
	int r1 = 0;
	arg_dup = ft_strdup(arg);
	(void) main;
	while (arg_dup[i])
	{
		printf("arg_dup : <%s>\n", arg_dup);
		if (arg_dup[j] == '$' && (arg_dup[j + 1] == ' ' || arg_dup[j + 1] == '=' || arg_dup[j + 1] == ':' || (arg_dup[j + 1] == '"' && in_dquote(main, arg_dup, j) == 1)))
		{
			printf("j : %d\n", j);
			j++;
		}
		while (arg_dup[j] != '$' && arg_dup[j])
		{
			if (j == main->s_qs[r])
			{
				printf("j : %d\n", j);
				j++;
				while (arg_dup[j] != '\'')
					j++;
				printf("j : %d\n", j);
				r++;
			}
			if (j == main->d_qs[r1])
				r1++;
			if (arg_dup[j] == '\\' && arg_dup[j + 1] == '$')
				j += 2;
			j++;
			if (arg_dup[j] == '$' && (arg_dup[j + 1] == ' ' || arg_dup[j + 1] == '=' || arg_dup[j + 1] == ':' || (arg_dup[j + 1] == '"' && in_dquote(main, arg_dup, j) == 1)))
			{
				printf("j : %d\n", j);
				j++;
			}
		}
		if (j > 0)
		{
			tmp = ft_substr(arg_dup, i, j - i);
			printf("tmp_debut : <%s>\n", tmp);
		}
		i = j;
		if (arg_dup[i] == '$')
			i += 1;
		while (arg_dup[i] != '$' && arg_dup[i] != '?' && arg_dup[i] != '=' && (arg_dup[i] != '"') && (arg_dup[i] != '\'') && arg_dup[i] != ' ' && arg_dup[i] != ':' && !ft_isdigit(arg_dup[i]) && arg_dup[i] != '%' && arg_dup[i] != '\\' && arg_dup[i])
			i++;
		if (arg_dup[i] == '$' || arg_dup[i] == '?' || arg_dup[i] == '=' || arg_dup[i] == '"' || arg_dup[i] == '\'' || arg_dup[i] == ' ' || arg_dup[i] == ':' || ft_isdigit(arg_dup[i]) || arg_dup[i] == '%' || arg_dup[i] == '\\')
		{
			if (((arg_dup[i] == '"' && main->d_qs[r1] == i) || (arg_dup[i] == '\'' && main->s_qs[r] == i)) && arg_dup[i - 1] == '$')
				check = 1;
			if ((arg_dup[i] == '?' || (arg_dup[i] >= '0' && arg_dup[i] <= '9')) && arg_dup[i - 1] == '$')
				i++;
			end = i;
			tmp3 = ft_substr(arg_dup, i, ft_strlen(arg_dup) - i);
			printf("tmp3_end : <%s>\n", tmp3);
		}
		else
			end = ft_strlen(arg_dup);
		tmp2 = ft_substr(arg_dup, j, end - j);
		printf("tmp2_dollar : <%s>\n", tmp2);
		int rep_pos = check_var_exists2(main, &tmp2[1]);
		replace(main, &tmp2, rep_pos, r, r1, check);
		printf("\n");
		printf("tmp_debut : <%s>\n", tmp);
		printf("tmp2_dollar replaced : %s\n", tmp2);
		printf("tmp3_end : <%s>\n", tmp3);
		final_tmp = attach_tmps(tmp, tmp2, tmp3);
		printf("final_tmp : <%s>\n", final_tmp);
		if ((size_t)end == ft_strlen(arg_dup))
		{
			if (tmp)
				free(tmp);
			if (tmp3)
				free(tmp3);
			free(tmp2);
			i = end;
		}
		else
		{
			printf("\n");
			arg_replace(&arg_dup, final_tmp);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			if (tmp3)
			{
				free(tmp3);
				tmp3 = NULL;
			}
			free(tmp2);
			tmp2 = NULL;
			free(final_tmp);
			final_tmp = NULL;
			i = 0;
			j = 0;
			end = 0;
			r = 0;
			r1 = 0;
		}
	}
	free(arg_dup);
	if (ft_strchr(final_tmp, '\\'))
		del_backslash(&final_tmp);
	return (final_tmp);
}

int	handle_sc(t_main *main, char **split, int i)
{
	int		sc_type;

	sc_type = is_sc(split[i]);
	if (sc_type == 1)
	{
		main->tokens[i].type = sc;
		return (1);
	}
	if (sc_type == 2)
	{
		main->tokens[i].type = argument;
		return (1);
	}
	return (0);
}
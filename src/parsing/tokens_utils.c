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

// char	*replace_dollar(char *s, t_main *main)
// {
// 	int		i;
// 	int		j;
// 	int		l;
// 	char	*res;
// 	char	*tmp;

// 	i = 0;
// 	res = 0;
// 	while (s[i])
// 	{
// 		j = i;
// 		while (s[j] && s[j] != '$')
// 			j++;
// 		if (j != i)
// 		{
// 			tmp = ft_substr(s, i, j - i);
// 			printf("substr : %s\n", tmp);
// 			res = ft_strjoin_free(res, tmp, 0);
// 			free(tmp);
// 			tmp = NULL;
// 		}
// 		if (s[i + 1] && (s[i + 1] == '$' || s[i + 1] == '?'))
// 		{
// 			printf("s[i + 1] return : %s\n", ft_strdup(s));
// 			return (ft_strdup(s));
// 		}
// 		i = j;
// 		if (s[i] == '$')
// 		{
// 			while (s[j] && s[j] != '=')
// 				j++;
// 			tmp = ft_substr(s, i, j - i);
// 			l = check_var_exists2(main, &tmp[1]);
// 			if (l >= 0)
// 				res = ft_strjoin_free(res, &ft_strchr(main->env[l], '=')[1], 0);
// 			free(tmp);
// 			tmp = NULL;
// 			i = j;
// 		}
// 	}
// 	return (res);
// }

void	replace(t_main *main, char **tmp2, int rep_pos)
{
	//printf("rep_pos : %d\n", rep_pos);
	if (ft_strcmp (*tmp2, "$") == 0)
		return ;
	if (rep_pos >= 0)
		*tmp2 = ft_strdup(&ft_strchr(main->env[rep_pos], '=')[1]);
	else if (rep_pos == -1)
		*tmp2 = ft_strdup("");
	else if (rep_pos == -2)
		*tmp2 = ft_strdup(ft_itoa(main->last_exit_code));
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

	i = 0;
	j = 0;
	end = 0;
	arg_dup = ft_strdup(arg);
	(void) main;
	while (arg_dup[i])
	{
		printf("arg_dup : %s\n", arg_dup);
		while (arg_dup[j] != '$' && arg_dup[j])
			j++;
		if (j > 0)
		{
			tmp = ft_substr(arg_dup, i, j - i);
			//printf("tmp_debut : %s\n", tmp);
		}
		i = j + 1;
		while (arg_dup[i] != '$' && arg_dup[i] != '?' && arg_dup[i] != '=' && arg_dup[i])
			i++;
		if (arg_dup[i] == '$' || arg_dup[i] == '?' || arg_dup[i] == '=')
		{
			if (arg_dup[i] == '?')
				i++;
			end = i;
			tmp3 = ft_substr(arg_dup, i, ft_strlen(arg_dup) - i);
			//printf("tmp3_end : %s\n", tmp3);
		}
		else
			end = ft_strlen(arg_dup);
		tmp2 = ft_substr(arg_dup, j, end - j);
		printf("tmp2_dollar : %s\n", tmp2);
		int rep_pos = check_var_exists2(main, &tmp2[1]);
		replace(main, &tmp2, rep_pos);
		printf("\n");
		printf("tmp_debut : %s\n", tmp);
		printf("tmp2_dollar replaced : %s\n", tmp2);
		printf("tmp3_end : %s\n", tmp3);
		final_tmp = attach_tmps(tmp, tmp2, tmp3);
		printf("final_tmp : %s\n", final_tmp);
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
		}
	}
	free(arg_dup);
	// printf("exit\n");
	// exit(0);
	//printf("final_tmp : %s\n", final_tmp);
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
		// int j = -1;
		// while (split[++j])
		// 	printf("split %d : %s\n", j, split[j]);
		split[i] = replace_dollar(split[i], main);
		main->tokens[i].type = argument;
		// j = -1;
		// while (split[++j])
		// 	printf("res split %d : %s\n", j, split[j]);
		return (1);
	}
	return (0);
}

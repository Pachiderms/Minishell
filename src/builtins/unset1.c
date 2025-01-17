/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:04:53 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:04:55 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_env(t_main *main, char *cmd) // trop de lignes
{
	int		i;
	int		j;
	int		var_to_unset;
	char	**tmp;

	i = 0;
	j = 0;
	var_to_unset = check_var_exists(main->env, main->env_len, cmd);
	if (var_to_unset == -1)
		return ;
	tmp = (char **)malloc(sizeof(char *) * (main->env_len + 1));
	remake_env(tmp, main, 0, -2);
	i = 0;
	while (i < main->env_len)
	{
		if (i == var_to_unset)
			i++;
		main->env[j] = ft_strdup(tmp[i]);
		i++;
		j++;
		if (i == var_to_unset)
			i++;
	}
	main->env[j] = NULL;
	free_env(tmp, main->env_len);
	main->env_len -= 1;
}

void	unset_export(t_main *main, char *cmd) // trop de lignes
{
	int		i;
	int		j;
	int		var_to_unset;
	char	**tmp;

	i = 0;
	j = 0;
	var_to_unset = check_var_exists(main->export, main->export_len, cmd);
	if (var_to_unset == -1)
		return ;
	tmp = (char **)malloc(sizeof(char *) * (main->export_len + 1));
	remake_env(tmp, main, 1, -2);
	i = 0;
	while (i < main->export_len)
	{
		if (i == var_to_unset)
			i++;
		main->export[j] = ft_strdup(tmp[i]);
		i++;
		j++;
		if (i == var_to_unset)
			i++;
	}
	main->export[j] = NULL;
	free_env(tmp, main->export_len);
	main->export_len -= 1;
}

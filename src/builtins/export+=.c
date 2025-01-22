/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:08:43 by zamgar            #+#    #+#             */
/*   Updated: 2024/11/18 15:08:45 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_plus(char *cmd)
{
	int		i;
	char	*arg;

	i = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	while (arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		return (1);
	return (0);
}

char	*get_without_plus(char *cmd)
{
	int		i;
	int		j;
	char	*arg;
	char	*str;

	i = 0;
	j = 0;
	arg = &ft_strchr(cmd, ' ')[1];
	str = (char *)malloc(sizeof(char) * ft_strlen(arg));
	while (arg[i])
	{
		if (arg[i] != '+')
		{
			str[j] = arg[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_plus_str(t_main *main, char *cmd)
{
	int		replace_pos;
	char	*arg;

	replace_pos = check_var_exists(main->env, main->env_len, cmd);
	if (replace_pos == -1)
		arg = ft_strjoin("export ", get_without_plus(cmd));
	else
		arg = ft_strjoin(ft_strjoin("export ", main->env[replace_pos]),
				&ft_strchr(cmd, '=')[1]);
	return (arg);
}

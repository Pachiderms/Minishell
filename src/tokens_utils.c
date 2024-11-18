#include "../includes/minishell.h"

char	**ft_double_array_clean(char **split)
{
	char	**res;
	int		i;
	int		len;

	i = 0;
	len = 1;
	while (split[++i])
	{
		if (!ft_strchr(split[i], 34) && !ft_strchr(split[i], 39))
		len++;
	}
	res = malloc ((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		res[i] = NULL;
		i++;
	}
	return (res);
}

char	*get_rid_of(char *s, char supr)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != supr)
		len++;
	}
	dest = malloc(len * sizeof(char) + 1);
	if (!dest)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != supr)
		dest[len++] = s[i];
	}
	dest[len++] = '\0';
	return (dest);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
}

int	ft_quote(char **s, char **split, int q)
{
	int		i;
	char	*tmp;

	i = 1;
	*s = get_rid_of(split[0], q);
	tmp = NULL;
	while (split[i])
	{
		if (ft_strchr(split[i], q))
		{
			tmp = ft_strjoin(" ", get_rid_of(split[i], q));
			*s = ft_strjoin(*s, tmp);
			break ;
		}
		else
			tmp = ft_strjoin(" ", get_rid_of(split[i], q));
		*s = ft_strjoin(*s, tmp);
		i++;
	}
	return (i + 1);
}

char	**clean_split(char **split)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = 0;
	res = ft_double_array_clean(split);
	if (!res)
		return (NULL);
	while (split[i])
	{
		if (ft_strchr(split[i], 34))
			i += ft_quote(&res[len++], &split[i], 34);
		else if (ft_strchr(split[i], 39))
			i += ft_quote(&res[len++], &split[i], 39);
		else
		{
			res[len] = split[i];
			len++;
			i++;
		}
	}
	res[len] = NULL;
	return (res);
}

int	init_tokens(char **split, t_main *main)
{
	int		i;
	i = 0;
	while (split[i] != NULL)
		i++;
	main->tokens = malloc(i * sizeof(t_token));
	if (!main->tokens)
		return (0);
	i = 0;
	while (split[i] != NULL)
	{
		if (is_cmd(split[i], main->path))
			main->tokens[i].type = command;
		else if (is_sc(split[i]))
			main->tokens[i].type = sc;
		else
			main->tokens[i].type = argument;
		main->tokens[i].value = split[i];
		i++;
	}
	return (1);
}

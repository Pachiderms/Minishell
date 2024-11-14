#include "../includes/minishell.h"

/* char    *super_join(char *s1, char *s2, int space)
{
    int i;
    int j;

    
} */

char    *get_rid_of(char *s, char supr)
{
    int     i;
    int     len;
    char    *dest;

    i = 0;
    len = 0;
    while (s[++i])
    {
        if (s[i] != supr)
            len++;
    }
    dest = malloc(len * sizeof(char) + 1);
    if (!dest)
        return (0);
    i = 0;
    len = 0;
    while (s[i])
    {
        if (s[i] != supr)
            dest[len++] = s[i];
        i++;
    }
    dest[len] = '\0';
    return (dest);
}

int	ft_quote(char **s, char **split, int q)
{
	int		i;
	char	*tmp;
	
	i = 1;
	*s = get_rid_of(*split, q);
	while (split[i])
	{
		if (ft_strchr(split[i], q))
		{
			tmp = ft_strjoin(" ", get_rid_of(split[i], q));
			*s = ft_strjoin(*s, tmp);
			break ;
		}
		tmp = ft_strjoin(" ", get_rid_of(split[i], q));
		*s = ft_strjoin(*s, tmp);
		i++;
	}
	return (i);
}

char	**clean_split(char **split)
{
	int		i;
	int		len;
	char	**res;
	i = 0;
	while (split[++i])
    {
        if (!ft_strchr(split[i], 34) && !ft_strchr(split[i], 39))
            len++;
    }
	res = malloc ((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], 34))
			i += ft_quote(&res[len++], &split[i], 34);
		else if (ft_strchr(split[i], 39))
			i += ft_quote(&res[len++], &split[i], 39);
		else
			res[len++] = split[i];
		i++;
	}
	res[len] = NULL;
	return (res);
}
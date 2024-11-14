#include "../includes/minishell.h"

int	ft_findmltpchar(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "echo", -1) || !ft_strncmp(s, "cd", -1)
		|| !ft_strncmp(s, "pwd", -1) || !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1) || !ft_strncmp(s, "env", -1)
		|| !ft_strncmp(s, "exit", -1))
		return (1);
	return (0);
}

int	is_cmd(char *s, char *path)
{
	int		i;
	char	*s1;
	char	**split;

	i = 0;
	s1 = ft_strjoin("/", s);
	split = ft_split(path, ':');
	while (split[i])
	{
		if (check_builtin(s))
			return (free(split), free(s1), 1);
		else if (access(ft_strjoin(split[i], s1), R_OK) == 0)
		{
			return (free(split), free(s1), 1);
		}
		i++;
	}
	return (free(split), free(s1), 0);
}

int	is_sc(char *s)
{
	if (ft_findmltpchar(s, "$|<>"))
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:08:42 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 21:08:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <strings.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

int PROCESSES;

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ss;
	char	*dest;

	i = 0;
	ss = (char *)s;
	while (ss[i] != '\0')
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (ss[i] != '\0')
	{
		dest[i] = ss[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_dup(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		size;
	char	*res;

	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	res = malloc(size * sizeof(char) + 1);
	if (!res)
		return (0);
	while (s1[i] && i + j < size)
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] && i + j < size)
	{
		res[j + i] = s2[j];
		j++;
	}
	res[j + i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	else
		return (ft_dup(s1, s2));
}

static size_t	ft_calca(char const *str, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 1)
		return (1);
	while (str[start] != '\0' && i < len)
	{
		i++;
		start ++;
	}
	return (i);
}

static char	*ft_gen(char *newstr, char const *str, unsigned int s, size_t len)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(str);
	while (s < strlen && i < len)
	{
		newstr[i] = str[s];
		i++;
		s++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t		strlen;
	char		*n;

	strlen = ft_strlen(str);
	if (!str)
		return (NULL);
	if (start > strlen || len <= 0)
	{
		n = (char *)malloc(sizeof(char) * 1);
		if (n == NULL)
			return (NULL);
		n[0] = '\0';
		return (n);
	}
	else
	{
		if (len > strlen)
			n = (char *)malloc(sizeof(char) * strlen + 1);
		if (len <= strlen)
			n = (char *)malloc(sizeof(char) * (ft_calca(str, start, len)) + 1);
		if (n == NULL)
			return (NULL);
	}
	return (ft_gen(n, str, start, len));
}
int	sizeup_no_space(char const *s) // trop de lignes
{
	size_t	i;
	int		size;

	i = 0;
	size = 0;
	while (isspace(s[i]) == 1)
		i++;
	while (i < ft_strlen(s))
	{
		if (isspace(s[i]) == 1)
		{
			while (isspace(s[i]) == 1)
				i++;
			if (s[i])
				size++;
		}
		if (s[i] == 34 || s[i] == 39)
		{
			i++;
			size++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
			{
				size++;
				i++;
			}
			if (s[i] == 34 || s[i] == 39)
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*get_rid_of_spaces(char const *s) // trop de lignes
{
	int		i;
	int		j;
	int		size;
	char	*no_space;

	i = 0;
	size = sizeup_no_space(s);
	no_space = malloc(sizeof(char) * size + 1);
	if (!no_space)
		return (NULL);
	i = 0;
	j = 0;
	while (isspace(s[i]) == 1)
		i++;
	while (j < size)
	{
		if (isspace(s[i]) == 1)
		{
			while (isspace(s[i]) == 1)
				i++;
			if (s[i])
				no_space[j++] = ' ';
		}
		if (s[i] == 34 || s[i] == 39)
		{
			no_space[j++] = s[i];
			i++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
			{
				no_space[j++] = s[i];
				i++;
			}
			if (s[i] == 34 || s[i] == 39)
				no_space[j++] = s[i];
		}
		else
			no_space[j++] = s[i];
		i++;
	}
	no_space[j] = '\0';
	return (no_space);
}

int	sizeup(char const *s, char c)
{
	int	size;
	int	i;

	if (s == 0 || s[0] == 0)
		return (-1);
	i = 1;
	size = 0;
	if (s[0] != c)
		size = 1;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			size++;
		i++;
	}
	return (size);
}

char	**ft_free(char **d, int start)
{
	while (start >= 0)
	{
		free(d[start]);
		start--;
	}
	free(d);
	return (0);
}

int	ft_calc(int i, int diff, char _c, char const *_s)
{
	if (diff == 1)
	{
		while (_s[i] != _c && _s[i])
			i++;
	}
	else if (diff == 0)
	{
		while (_s[i] == _c && _s[i])
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		x;
	int		size;
	char	**dest;

	i = 0;
	x = 0;
	j = 0;
	size = sizeup(s, c);
	dest = malloc((size + 1) * sizeof(char *));
	if (dest == NULL || s == 0)
		return (0);
	while (size-- > 0)
	{
		i = ft_calc(i, 0, c, s);
		j = ft_calc(i, 1, c, s);
		dest[x] = ft_substr(s, i, j - i);
		if (dest[x] == NULL)
			return (ft_free(dest, x));
		x++;
		i += (j - i);
	}
	dest[x] = 0;
	return (dest);
}


char	*get_rid_of(char *s, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			len++;
	}
	tmp = malloc(len * sizeof(char) + 1);
	if (!tmp)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != c)
			tmp[len++] = s[i];
	}
	tmp[len++] = '\0';
	return (tmp);
}

int	handle_opening_outfile(char *file, int append)
{
	int	fd;

	fd = -1;
	if (append)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			return (-1);
		if (access(file, W_OK) != 0)
		{
			close(fd);
			return (-1);
		}
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (-1);
		if (access(file, W_OK) != 0)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

int	handle_opening_infile(char *file, int append)
{
	int		fd;

	fd = -1;
	if (append) // heredoc
		return (-1);
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (access(file, R_OK) != 0)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

int	get_fd_out(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (cmd[i] && strcmp(cmd[i], "|") != 0)
	{
		if (strcmp(cmd[i], ">>") == 0)
		{
			if (cmd[i + 1])
				fd = handle_opening_outfile(cmd[i + 1], 1);
			else
				return (-1);
		}
		else if (strcmp(cmd[i], ">") == 0)
		{
			if (cmd[i + 1])
				fd = handle_opening_outfile(cmd[i + 1], 0);
			else
				return (-1);
		}
		i++;
	}
	return (fd);
}

int	get_fd_in(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && strcmp(cmd[i], "|") != 0)
	{
		if (strcmp(cmd[i], "<") == 0)
		{
			if (cmd[i + 1])
				return (handle_opening_infile(cmd[i + 1], 0));
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*prep_process(char *s)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = NULL;
	if (strchr(s, '<') || strchr(s, '>'))
	{
		res = get_rid_of_spaces(s);
		tmp = get_rid_of(res, '<');
		free(res);
		res = get_rid_of(tmp, '>');
		free(tmp);
		tmp = get_rid_of_spaces(res);
		return (free(res), tmp);
	}
	return (get_rid_of_spaces(s));
}

int	ft_exec(char **cmd)
{
	char **_cmd = cmd;
	char *buf;
	_cmd[2] = NULL;
	// for(int i=0;i<3;i++)
	// 	printf("cmd %d : %s\n", i, _cmd[i]);
	execve(ft_strjoin("/usr/bin/", _cmd[0]), _cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	ft_fork(char **cmd)
{
	pid_t	fork_id;
	int		exit_code;

	fork_id = fork();
	exit_code = 0;
	if (fork_id == 0)
	{
		exit_code = ft_exec(cmd);
	}
	else
	{
		waitpid(fork_id, NULL, 0);
	}
	return (exit_code);
}

void    close_pipes(int pipes[PROCESSES][2], int me)
{
    int i;

    i = 0;
    while (i < PROCESSES)
    {
        if (i != me)
            close(pipes[i][0]);
        // if (i + plus != no)
        close(pipes[i][1]);
        i++;
    }
}

void	close_all_pipes(int pipes[PROCESSES][2])
{
	int i;

    i = 0;
    while (i < PROCESSES)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
}

void	ft_wait(int pids[PROCESSES])
{
	int	i;

	i = 0;
	while (i < PROCESSES)
		waitpid(pids[i], NULL, 0);
}

int	ft_pipe(char **processes, int argc)
{
	pid_t	child_pid[PROCESSES];
	pid_t	fork_id;
	int		fd[PROCESSES][2];
	int		fdin;
	int		fdout;
	int		i;
	int		j;

	i = -1;
	while (++i < PROCESSES)
	{
		if (pipe(fd[i]) < 0)
			return (perror("pipe fail"), 1);
	}
	fdin = get_fd_in(&processes[0]);
	dup2(fdin, STDIN_FILENO);
	i = 0;
	j = 0;
	while (j < PROCESSES - 1)
	{
		child_pid[j] = fork();
		if (child_pid[j] < 0)
			return (perror("fork fail"), 1);
		if (child_pid[j] == 0)
		{
			for(int k=i;k<2;k++)
				printf("cmd %d : %s\n", k, processes[k]);
			dup2(fd[j][1], STDOUT_FILENO);
			close_all_pipes(fd);
			ft_exec(&processes[i]);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(fd[j][0], STDIN_FILENO);
			close(fd[j][1]);
			i += 2;
			j++;
		}	
	}
	printf("i=%d\n", i);
	fork_id = fork();
	if (fork_id == 0)
	{
		printf("last:%s\n", processes[argc - 3]);
		fdout = get_fd_out(&processes[argc - 3]);
		printf("fdout=%d\n", fdout);
		printf("dup=%d\n", dup2(fdout, STDOUT_FILENO));
		close_all_pipes(fd);
		ft_exec(&processes[argc - 3]);
	}
	dup2(0, fd[j][0]);
	dup2(1, fd[j][1]);
	close_all_pipes(fd);
	i = -1;
	while (++i < PROCESSES)
		waitpid(child_pid[i], NULL, 0);
	waitpid(fork_id, NULL, 0);
	return (1);
}

int	launch_process(char **processes, int argc)
{
	int	exit_code;

	if (PROCESSES < 2)
		exit_code = ft_fork(processes);
	else
		exit_code = ft_pipe(processes, argc);
	return (exit_code);
}
int	main(int argc, char **argv)
{
	PROCESSES = (argc - 1) /  2;
	if (PROCESSES == 0)
		PROCESSES = 1;
	printf("argv 0 %s %d\n", argv[0], PROCESSES);
	int exit_code = 0;
	char *cmd;
	while (1)
	{
		cmd = readline("enter something ");
		exit_code = launch_process(&argv[1], argc);
		if (cmd == NULL){
			printf("exit\n");
			break ;
		}
	}
	free(cmd);
	return (exit_code);
}
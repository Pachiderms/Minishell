
#include "includes/test.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int		status;
	pid_t	fork_id;
	while (1)
	{
		char *cmd = readline("Waiting for command: ");
		char **split = ft_split(cmd, ' ');
		if (access(split[1], X_OK) != 0)
			break ;
		fork_id = fork();
		if (fork_id == 0)
			execve(ft_strjoin(ft_strdup("/bin/"), split[0]), split, NULL);
		else
			waitpid(fork_id, &status, 0);
	}
}

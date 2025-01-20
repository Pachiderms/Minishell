/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:36:18 by marvin            #+#    #+#             */
/*   Updated: 2025/01/20 15:36:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	pid_t	child_pid;
	pid_t	fork_id;
	int		fd[2];
	int		fdin;

	if (pipe(fd) < 0)
		return (perror("pipe fail"), 1);
	fdin = get_fd_in(&processes[0]);
	dup2(fdin, STDIN_FILENO);
	child_pid = fork();
	if (child_pid < 0)
		return (perror("fork fail"), 1);
	if (child_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_exec(main, &processes[0]);
		exit(EXIT_FAILURE);
	}
	fork_id = fork();
	if (fork_id == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		ft_exec(main, &processes[1]);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(child_pid, NULL, 0);
	waitpid(fork_id, NULL, 0);
	return (1);
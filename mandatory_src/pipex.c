/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/07 15:16:48 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	setup_and_execute(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	**env;

	int (pid1), (pid2);
	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	if (argc <= 4)
		return (ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]), 1);
	env = extract_path(envp);
	pid1 = fork();
	if (pid1 == 0)
		handle_first_child(fd, argv, env, envp);
	pid2 = fork();
	if (pid2 == 0)
		handle_second_child(fd, argv, env, envp);
	free_two_d_array(env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	return (setup_and_execute(argc, argv, envp));
}







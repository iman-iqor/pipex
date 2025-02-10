/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/10 17:10:30 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **env, char **envp)
{
	char	**av;
	char	*exact_path;
	int		code;

	av = ft_split(cmd, ' ');
	if (!av || !av[0])
	{
		free_two_d_array(env);
		free_two_d_array(av);
		ft_fprintf(2, "Invalid command => empty\n");
		exit(1);
	}
	if (open(cmd, __O_DIRECTORY) != -1)
	{
		free_two_d_array(env);
		free_two_d_array(av);
		ft_fprintf(2, "%s is a directory", cmd);
		exit(1);
	}
	exact_path = check_path(env, av[0]);
	code = ft_execve(exact_path, av, envp);
	free_two_d_array(env);
	free_two_d_array(av);
	exit(code);
}

int	setup_and_execute(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**env;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	if (argc < 5 || argc > 4)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:28:11 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/08 21:06:25 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file_for_reading(char *filename, char **env)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_two_d_array(env);
		perror(filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_file_for_writing(char *filename, char **env)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < 0)
	{
		free_two_d_array(env);
		perror(filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_execve(char *exact_path, char **av, char **envp)
{
	if (strchr(exact_path, '/') && execve(exact_path, av, envp) == -1)
	{
		if (access(exact_path, F_OK) == 0 && access(exact_path, X_OK) == -1)
			ft_fprintf(2, "%s:permission denied\n", exact_path);
		else if (access(exact_path, F_OK) != 0)
			ft_fprintf(2, "%s:command not found\n", exact_path);
		free_two_d_array(av);
		exit(1);
	}
	else
	{
		ft_fprintf(2, "%s:command not found\n", exact_path);
	}
}

void	execute_command(char *cmd, char **env, char **envp)
{
	char	**av;
	char	*exact_path;

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
	ft_execve(exact_path, av, envp);
}

void	handle_first_child(int *fd, char **argv, char **env, char **envp)
{
	int	f1;

	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	f1 = open_file_for_reading(argv[1], env);
	dup2(f1, 0);
	close(f1);
	execute_command(argv[2], env, envp);
}

void	handle_second_child(int *fd, char **argv, char **env, char **envp)
{
	int	f2;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	f2 = open_file_for_writing(argv[4], env);
	dup2(f2, 1);
	close(f2);
	execute_command(argv[3], env, envp);
}

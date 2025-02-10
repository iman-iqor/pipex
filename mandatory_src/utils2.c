/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:28:11 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/10 15:15:43 by imiqor           ###   ########.fr       */
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

int	ft_execve(char *exact_path, char **av, char **envp)
{
	if (strchr(exact_path, '/') && execve(exact_path, av, envp) == -1)
	{
		if (access(exact_path, F_OK) == 0 && access(exact_path, X_OK) == -1)
			ft_fprintf(2, "%s:permission denied\n", exact_path);
		else if (access(exact_path, F_OK) != 0)
			ft_fprintf(2, "%s:command not found\n", exact_path);
	}
	else
		ft_fprintf(2, "%s:command not found\n", exact_path);
	return (0);
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

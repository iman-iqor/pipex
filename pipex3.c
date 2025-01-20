/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/20 14:40:49 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include "libft/libft.h"
#include "ft_fprintf/ft_fprintf.h"
#include "ft_printf/ft_printf.h"

char	**extract_path(char **envp1)
{
	int		i;
	char	**two_d_paths;

	i = 0;
	while (envp1[i])
	{
		if (ft_strncmp(envp1[i], "PATH=", 5) == 0)
		{
			two_d_paths = ft_split(envp1[i] + 5, ':');
			return (two_d_paths);
		}
		i++;
	}
	return (NULL);
}

char	*concatenate_path(char *oneDfromthetwoDpath, char *command_name)
{
	char	*path;
	char	*full_path;

	path = NULL;
	full_path = NULL;
	if (!oneDfromthetwoDpath)
		return (NULL);
	path = ft_strjoin(oneDfromthetwoDpath, "/");
	full_path = ft_strjoin(path, command_name);
	free(path);
	return (full_path);
}

void	free_two_d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


static char *check_command(char *path, char **twoDpath, char *o)
{
    if (access(path, F_OK) == 0 && !o)
        o = path;
    if (access(path, X_OK) == 0)
    {
        free_two_d_array(twoDpath);
        if (o != path)
            free(o);
        return path;
    }
    if (o != path)
        free(path);
    return NULL;
}


char *check_path(char **twoDpath, char *command_name)
{
    int i = 0;
    char *path = NULL;
    char *o = NULL;

    if (access(command_name, F_OK | X_OK) != -1)
        return ft_strdup(command_name);

    while (twoDpath[i])
    {
        path = concatenate_path(twoDpath[i], command_name);
        char *result = check_command(path, twoDpath, o);
        if (result)
            return result;
        i++;
    }
    free_two_d_array(twoDpath);
    return o;
}

int	open_file_for_reading(char *filename, char **env)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_two_d_array(env);
		perror("open file1");
	}
	return (fd);
}

int	open_file_for_writing(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < 0)
		perror(filename);
	return (fd);
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
		perror("Invalid command");
		exit(1);
	}
	exact_path = check_path(env, av[0]);
	if (execve(exact_path, av, envp) == -1)
	{
		perror("Execution failed");
		free_two_d_array(av);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		f1;
	int		f2;
	char	**env;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	if (argc <= 4)
		return (ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]), 1);
	env = extract_path(envp);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		f1 = open_file_for_reading(argv[1], env);
		dup2(f1, 0);
		close(f1);
		dup2(fd[1], 1);
		close(fd[1]);
		execute_command(argv[2], env, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		f2 = open_file_for_writing(argv[4]);
		dup2(f2, 1);
		close(f2);
		dup2(fd[0], 0);
		close(fd[0]);
		execute_command(argv[3], env, envp);
	}
	free_two_d_array(env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

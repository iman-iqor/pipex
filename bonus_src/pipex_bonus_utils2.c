/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:14:39 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/08 17:18:01 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execve(char *exact_path, char **av, char **envp)
{
	if (execve(exact_path, av, envp) == -1)
	{
		perror(exact_path);
		free_two_d_array(av);
		exit(1);
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

void	free_two_d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
	{
		return ;
	}
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	check_pipe_is_valid(int pipe_return)
{
	if (pipe_return == -1)
	{
		ft_fprintf(2, "Pipe failed a ptipana");
		exit(-1);
	}
}

void	dup2_and_close_pipe_fds(int fd1, int fd2, int mode)
{
	int	dup_ret;

	close(fd1);
	dup_ret = dup2(fd2, mode);
	if (dup_ret == -1)
	{
		ft_fprintf(2, "Dup2 Failed\n");
		exit(EXIT_FAILURE);
	}
	close(fd2);
}

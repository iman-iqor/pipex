/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:14:39 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/10 00:36:26 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_execve(char *exact_path, char **av, char **envp)
{
	if (strchr(exact_path, '/') && execve(exact_path, av, envp) == -1)
	{
		if (access(exact_path, F_OK) == 0 && access(exact_path, X_OK) == -1)
			ft_putstr(exact_path, ":permission denied\n");
		else if (access(exact_path, F_OK) != 0)
			ft_putstr(exact_path, ":command not found\n" );
	}
	else
		ft_putstr(exact_path, ":command not found\n");
	return (0);
}


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
		ft_putstr("Invalid", " command => empty\n");
		exit(1);
	}
	if (open(cmd, __O_DIRECTORY) != -1)
	{
		free_two_d_array(env);
		free_two_d_array(av);
		ft_putstr(cmd,"is a directory");
		exit(1);
	}
	exact_path = check_path(env, av[0]);
	code = ft_execve(exact_path, av, envp);
	free_two_d_array(env);
	free_two_d_array(av);
	exit(code);
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
		perror("Pipe");
		exit(-1);
	}
}

void	dup2_and_close_pipe_fds(int fd1, int fd2, int mode)
{
	close(fd1);
	dup2(fd2, mode);
	close(fd2);
}

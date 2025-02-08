/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:22:18 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/08 17:23:28 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_output_filee_here_doc_util(char *filename, char **env)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		free_two_d_array(env);
		perror(filename);
	}
	return (fd);
}

void	handle_first_child(int *fd, char **argv, char **env, char **envp)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	execute_command(argv[3], env, envp);
}

void	handle_second_child(int *fd, char **argv, char **env, char **envp)
{
	int	f2;

	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	f2 = open_output_filee_here_doc_util(argv[5], env);
	dup2(f2, 1);
	close(f2);
	execute_command(argv[4], env, envp);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (str1[i] && str2[i] && str1[i] == str2[i])
	{
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	here_doc_exist(char *argv1)
{
	if (ft_strcmp(argv1, "here_doc") == 0)
		return (1);
	return (0);
}

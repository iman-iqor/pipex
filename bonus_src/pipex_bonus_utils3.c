/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:14:28 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/08 17:16:59 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	dup2_and_close_file_fd(int fd, int mode)
{
	int	dup_ret;

	dup_ret = dup2(fd, mode);
	if (dup_ret == -1)
	{
		ft_fprintf(2, "Dup2 Failed\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	open_input_file(char *filename, char **env)
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

int	open_output_file(char *filename, char **env)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free_two_d_array(env);
		perror(filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	check_fork(int fork_ret, char **env)
{
	if (fork_ret == -1)
	{
		free_two_d_array(env);
		ft_fprintf(2, "Fork failed\n");
		exit(-1);
	}
}

void	check_argc(int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
		{
			ft_fprintf(2, "usage not fin e\n");
			exit(1);
		}
	}
	else
	{
		if (argc < 5)
		{
			write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 50);
			exit(1);
		}
	}
}

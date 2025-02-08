/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_d oc_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:22:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/08 17:30:16 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*here_doc_wih_get_next_line(char *argv1, char *argv2)
{
	char	*buffer;
	char	*s;
	int		str_cmp_rtn;

	buffer = NULL;
	s = NULL;
	argv2 = ft_strjoin(argv2, "\n");
	if (here_doc_exist(argv1))
	{
		str_cmp_rtn = 1;
		while (str_cmp_rtn != 0)
		{
			s = get_next_line(0);
			str_cmp_rtn = ft_strcmp(s, argv2);
			if (str_cmp_rtn != 0)
				buffer = ft_sstrjoin(buffer, s);
			free(s);
		}
		free(argv2);
		get_next_line(-1);
		return (buffer);
	}
	return (NULL);
}

void	pipe_is_valid(int pipe_return)
{
	if (pipe_return == -1)
	{
		ft_fprintf(2, "pipe failed\n");
		exit(-1);
	}
}

void	fork_is_valid(int fork_return)
{
	if (fork_return == -1)
	{
		ft_fprintf(2, "fork failed\n");
		exit(-1);
	}
}

void	close_and_dup2_pipe_fds(int fd1, int fd2, int mode)
{
	close(fd1);
	dup2(fd2, mode);
	close(fd2);
}

int	setup_and_execute(int argc, char **argv, char **envp)
{
	char	**env;
	int		fd[2];
	int		pid1;
	int		pid2;

	pipe_is_valid(pipe(fd));
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

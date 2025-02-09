/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:06:47 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/09 15:18:43 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_pipe_and_fork(char **argv, char **envp)
{
	char	*str;
	int		fd[2];

	if (!here_doc_exist(argv[1]))
		return (1);
	str = here_doc_wih_get_next_line(argv[1], argv[2]);
	pipe_is_valid(pipe(fd));
	write(fd[1], str, ft_strlen(str));
	free(str);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	setup_and_execute(argv, envp);
	return (0);
}

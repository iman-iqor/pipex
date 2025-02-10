/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:14:49 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/10 14:52:23 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_all_pipex(void)
{
	while (wait(NULL) > 0)
		;
}

void	init_state(t_state *state, int argc, char **argv, char **envp)
{
	state->i = 2;
	state->env = extract_path(envp);
	state->fd1 = open_input_file(argv[argc - 1], argv[1], state->env);
	dup2_and_close_file_fd(state->fd1, 0);
	state->fd1 = open_output_file(argv[argc - 1], state->env);
	dup2_and_close_file_fd(state->fd1, 1);
}

void	in_parent(t_state state, int *in_fd)
{
	if (*in_fd)
		close(*in_fd);
	close(state.fd[1]);
	*in_fd = state.fd[0];
}

void	child(t_state state, int argc, char **argv, char **envp)
{
	if (state.fd1)
		dup2_and_close_pipe_fds(-1, state.fd1, 0);
	if (state.i != argc - 2)
		dup2_and_close_pipe_fds(state.fd[0], state.fd[1], 1);
	execute_command(argv[state.i], state.env, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;
	int		in_fd;

	in_fd = 0;
	ft_memset(&state, 0, sizeof(state));
	check_argc(argc, argv);
	if (!ft_pipe_and_fork(argv, envp))
		return (0);
	init_state(&state, argc, argv, envp);
	while (state.i < argc - 1)
	{
		if (state.i != argc - 2)
			check_pipe_is_valid(pipe(state.fd));
		state.pid = fork();
		check_fork(state.pid, state.env);
		state.fd1 = in_fd;
		if (state.pid == 0)
			child(state, argc, argv, envp);
		in_parent(state, &in_fd);
		state.i++;
	}
	wait_all_pipex();
	free_two_d_array(state.env);
}

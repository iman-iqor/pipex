/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:14:49 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/06 21:11:02 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*check_path(char **twoDpath, char *command_name)
{
	int		i;
	char	*path;
	char	*o;
	char	*result;

	i = 0;
	path = NULL;
	o = NULL;
	if (access(command_name, F_OK | X_OK) != -1)
		return (ft_strdup(command_name));
	while (twoDpath[i])
	{
		path = concatenate_path(twoDpath[i], command_name);
		result = check_command(path, twoDpath);
		if (result)
			return (result);
		i++;
	}
	free_two_d_array(twoDpath);
	return (NULL);
}

char	**extract_path(char **envp1)
{
	int		i;
	char	**two_d_paths;

	i = 0;
	if (!envp1)
	{
		return (NULL);
	}
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

char	*check_command(char *path, char **twoDpath)
{
	if (access(path, F_OK | X_OK) == 0)
	{
		free_two_d_array(twoDpath);
		return (path);
	}
	return (NULL);
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
	if (execve(exact_path, av, envp) == -1)
	{
		ft_fprintf(2, "%s: Failed during execve\n", exact_path);
		free_two_d_array(av);
		exit(1);
	}
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

void	check_argc(int argc)
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 50);
		exit(1);
	}
}

void	wait_all_pipex(void)
{
	while (wait(NULL) > 0)
		continue ;
}

void	init_state(t_state *state, int argc, char **argv, char **envp)
{
	state->i = 2;
	state->env = extract_path(envp);
	state->fd1 = open_input_file(argv[1], state->env);
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
	if (state.i && state.fd1)
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
	if (!ft_pipe_and_fork(argv, argc, envp))
		return (0);
	check_argc(argc);
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
		else
			in_parent(state, &in_fd);
		state.i++;
	}
	wait_all_pipex();
	free_two_d_array(state.env);
}

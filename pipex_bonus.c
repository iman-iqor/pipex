#include"pipex_bonus.h"


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
		result = check_command(path, twoDpath, o);
		if (result)
			return (result);
		i++;
	}
	free_two_d_array(twoDpath);
	return (o);
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

char	*check_command(char *path, char **twoDpath, char *o)
{
	if (access(path, F_OK) == 0 && !o)
		o = path;
	if (access(path, X_OK) == 0)
	{
		free_two_d_array(twoDpath);
		if (o != path)
			free(o);
		return (path);
	}
	if (o != path)
		free(path);
	return (NULL);
}

void	execute_command(char *cmd, char **env, char **envp)
{
	char	**av;
	char	*exact_path;

	ft_fprintf(2, "CMD: %s\n", cmd);
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
		ft_fprintf(2, "%s is a diirectory", cmd);
		exit(1);
	}
	exact_path = check_path(env, av[0]);
	if (execve(exact_path, av, envp) == -1)
	{
		ft_fprintf(2, "%s: Failed during execve\n", exact_path);
		//perror(exact_path);
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
int	open_input_file(char *filename,char** env)
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

int	open_output_file(char *filename,char** env)
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

int	main(int argc, char **argv, char **envp)
{
	int	n;
	int	i;
	int	fd[2];
	int pid;
	int fd1;
	char **env;

	if (argc >= 5)
	{
		n = argc - 3;
		i = 0;
		env = extract_path(envp);
		while (i <= n)
		{
			if (i == 0)
			{
				// first command
				check_pipe_is_valid(pipe(fd));
				pid = fork();
				check_fork(pid, env);
				if (pid == 0)
				{
					dup2_and_close_pipe_fds(fd[0], fd[1], 1);
					fd1 = open_input_file(argv[1],env);
					dup2_and_close_file_fd(fd1, 0);
					execute_command(argv[2], env, envp);
				}
				else
					dup2_and_close_pipe_fds(fd[1], fd[0], 0);
			}
			else if (i == n - 1)
			{
				// last command
				check_pipe_is_valid(pipe(fd));
				pid = fork();
				check_fork(pid, env);
				if (pid == 0)
				{
					dup2_and_close_pipe_fds(fd[1], fd[0], 0);
					fd1 = open_output_file(argv[argc - 1],env);
					dup2_and_close_file_fd(fd1, 1);
					execute_command(argv[argc-2], env, envp);
				}
			}
			else
			{
				// middle commands
				check_pipe_is_valid(pipe(fd));
				pid = fork();
				check_fork(pid, env);
				if (pid == 0)
				{
					dup2_and_close_pipe_fds(fd[0], fd[1], 1);
					execute_command(argv[i + 1], env, envp);
				}
				else
					dup2_and_close_pipe_fds(fd[1], fd[0], 0);
			}
			i++;
		}
	}
	else
		ft_printf("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n");
	return (0);
}

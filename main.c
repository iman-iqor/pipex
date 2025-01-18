/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/18 16:13:03 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*check_path(char **twoDpath, char *command_name)
{
	int		i;
	char	*path;
	char	*o;

	i = 0;
	o = NULL;
	if(access(command_name,F_OK|X_OK) != -1)
		return (ft_strdup(command_name));
	
	while (twoDpath[i])
	{
		path = NULL;
		path = concatenate_path(twoDpath[i], command_name);
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
		i++;
	}
	free_two_d_array(twoDpath);
	return (o);
}

int execute_commands(char **argv, 
        char **env, char **envp)
{
    int     pid1;
    int     pid2;
    char    **av;
    int     fd[2];
    int     input;
    int     output;
    char    *found_path;

    if(pipe(fd) == -1) 
        return (perror("pipe:"),-1);
    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd[0]);
        input = open(argv[1], O_RDONLY);
        if(input < 0)
		{
			free_two_d_array(env);
            return (perror("open file1: "),1);
		}
        dup2(input, 0);
        close(input);
        dup2(fd[1], 1);
        close(fd[1]);
        av = ft_split(argv[2], ' '); 
		if (!av || !av[0])
                return (free_two_d_array(env), free_two_d_array(av),perror("u passed null command a ptipana"),1);
        found_path = check_path(env, av[0]);
        if (execve(found_path, av, envp) == -1)
            exit ((perror("cmd1 error:"), free(av),1));
    }
    pid2 = fork();
    if(pid2 == 0)
    {
        close(fd[1]);
		output = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
        if(output < 0)
        {
			free_two_d_array(env);
            return (perror(argv[4]), 1);
        }
        dup2(output, 1);
        close(output);
        dup2(fd[0], 0);
        close(fd[0]);
        av = ft_split(argv[3], ' ');
        if (!av || !av[0])
                return (free_two_d_array(env),free_two_d_array(av),perror("u passed null command a ptipana"),1);
        char *exact_path_2 = check_path(env, av[0]);
        if (execve(exact_path_2,av,envp) == -1)
		{
			free_two_d_array(av);
			free(exact_path_2);
            exit((perror("cmd2 error:"), 1));
		}
    }
	free_two_d_array(env);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    char    **env;
    int     res;

    if(argc <=4)
        return (ft_printf("pipe usage:program name + file1.txt + cmd1 + cmd2 + file2.txt  at  least in the mandatory"),1);
    env = extract_path(envp);
    res = execute_commands(argv, env, envp);
    printf("Hello");
    if (res == -1)
        return (1);
    return (0);
}

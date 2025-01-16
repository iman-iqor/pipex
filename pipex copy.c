/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/16 22:41:29 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
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

int main(int argc, char **argv, char **envp)
{
    int     fd[2];
    int     pid1;
    int     pid2;
    int     f1;
	int 	f2;
    char    **env;
    char    **av;
	char 	*exact_path_1;

    if(pipe(fd) == -1) 
        return (perror("pipe:"),-1);
    if(argc <=4)
        return (ft_printf("pipe usage:program name + file1.txt + cmd1 + cmd2 + file2.txt  at  least in the mandatory"),1);
    env = extract_path(envp);
    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd[0]);
        f1 = open(argv[1], O_RDONLY);
        if(f1 < 0)
            return (perror("open file1: "),1);
        dup2(f1, 0);
        close(f1);
        dup2(fd[1], 1);
        close(fd[1]);
        av = ft_split(argv[2], ' '); 
		if (!av || !av[0])
                return (free_two_d_array(env), free_two_d_array(av),perror("u passed null command a ptipana"),1);
        exact_path_1 = check_path(env, av[0]);
        if (execve(exact_path_1, av, envp) == -1)
            exit ((perror("cmd1 error:"),free(av),1));
    }
    pid2 = fork();
    if(pid2 == 0)
    {
        close(fd[1]);
		f2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
        if(f2 < 0)
            return (perror(argv[4]), 1);
        dup2(f2, 1);
        close(f2);
        dup2(fd[0], 0);
        close(fd[0]);
        av = ft_split(argv[3], ' ');
		
        if (!av || !av[0])
                return (free_two_d_array(env),free_two_d_array(av),perror("u passed null command a ptipana"),1);
        char *exact_path_2 = check_path(env, av[0]);
        if (execve(exact_path_2,av,envp) == -1)
            exit((perror("cmd2 error:"), 1));
    }
    free_two_d_array(env);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
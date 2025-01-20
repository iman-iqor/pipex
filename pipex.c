/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/20 17:31:11 by imiqor           ###   ########.fr       */
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
	char	*allpathinone_d_path;
	char	**two_d_paths;

	i = 0;
	while (envp1[i])
	{
		allpathinone_d_path = ft_strnstr(envp1[i], "PATH", 4);
		if (allpathinone_d_path)
		{
			two_d_paths = ft_split(allpathinone_d_path + 5, ':');
			return (two_d_paths);
		}
		i++;
	}
	return (NULL);
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:32 by imiqor            #+#    #+#             */
/*   Updated: 2025/01/16 21:23:14 by imiqor           ###   ########.fr       */
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
	char	*allpathinone_d_path;
	char	**two_d_paths;

	i = 0;
	while (envp1[i])
	{
		allpathinone_d_path = ft_strnstr(envp1[i], "PATH", 4);
		if (allpathinone_d_path)
		{
			two_d_paths = ft_split(allpathinone_d_path + 5, ':');
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
    int fd[2];
    int pid1;
    int pid2;
    char **env;
    
    if(pipe(fd) == -1) 
        return (perror("pipe:"),-1);
    if(argc <=4)
    {
        ft_printf("pipe usage:program name + file1.txt + cmd1 + cmd2 + file2.txt  at  least in the mandatory");
        return 1;
    }
    env = extract_path(envp);
    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd[0]);
        
        int f = open(argv[1], O_RDONLY);
        if(f < 0)
        {
            perror("open file1: ");
            return 1;
        }
        dup2(f,0);
        close(f);

        dup2(fd[1] , 1);
        close(fd[1]);

        char **av = ft_split(argv[2], ' ');
        if (!av || !av[0])
	{
	    free_two_d_array(env);
	    free_two_d_array(av);
            perror("ft_split error");
                return 1;
        }
        char *exact_path = check_path(env,av[0]);
        if (execve(exact_path,av,envp) == -1)
        {
            perror("cmd1 error:");
            free(av);
            return 1;
        }
    }

    pid2 = fork();

    if(pid2 == 0)
    {
        close(fd[1]);

        int f = open(argv[4], O_WRONLY);

        if(f < 0)
        {
            perror("open file2:");
            return 1;
        }

        dup2(f,1);
        close(f);
        
        dup2(fd[0], 0); // Redirect pipe read-end to stdin
        close(fd[0]);

        char **av = ft_split(argv[3], ' ');
        if (!av || !av[0])
	{
	    free_two_d_array(env);
	    free_two_d_array(av);
            perror("ft_split error");
                return 1;
	}
        char *exact_path = check_path(env,av[0]);
	    free_two_d_array(env);
        if (execve(exact_path,av,envp) == -1)
        {
            perror("cmd2 error:");
            return 1;
        }
    }
    free_two_d_array(env);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 1);
    waitpid(pid2, NULL, 1);
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
    int fd[2];
    int pid1;
    int pid2;
    char **env;
    
    if(pipe(fd) == -1) 
        return (perror("pipe:"),-1);
    if(argc <=4)
    {
        ft_printf("pipe usage:program name + file1.txt + cmd1 + cmd2 + file2.txt  at  least in the mandatory");
        return 1;
    }
    env = extract_path(envp);
    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd[0]);
        
        int f = open(argv[1], O_RDONLY);
        if(f < 0)
        {
            perror("open file1: ");
            return 1;
        }
        dup2(f,0);
        close(f);

        dup2(fd[1] , 1);
        close(fd[1]);

        char **av = ft_split(argv[2], ' ');
        if (!av || !av[0])
	{
	    free_two_d_array(env);
	    free_two_d_array(av);
            perror("ft_split error");
                return 1;
        }
        char *exact_path = check_path(env,av[0]);
        if (execve(exact_path,av,envp) == -1)
        {
            perror("cmd1 error:");
            free(av);
            return 1;
        }
    }

    pid2 = fork();

    if(pid2 == 0)
    {
        close(fd[1]);

        int f = open(argv[4], O_WRONLY | O_TRUNC);

        if(f < 0)
        {
            perror("open file2:");
            return 1;
        }

        dup2(f,1);
        close(f);
        
        dup2(fd[0], 0); // Redirect pipe read-end to stdin
        close(fd[0]);

        char **av = ft_split(argv[3], ' ');
        if (!av || !av[0])
	    {
	    free_two_d_array(env);
	    free_two_d_array(av);
            perror("ft_split error");
                return 1;
	    }
        char *exact_path = check_path(env,av[0]);
	    free_two_d_array(env);
        if (execve(exact_path,av,envp) == -1)
        {
            perror("cmd2 error:");
            return 1;
        }
    }
    free_two_d_array(env);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 1);
    waitpid(pid2, NULL, 1);
}


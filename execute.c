#include "ft_fprintf/ft_fprintf.h"
#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

char	**extract_path(char **envp1)
{
	int		i;
	char	*allpathinoneDpath;
	char	**twoDpaths;

	i = 0;
	while (envp1[i])
	{
		allpathinoneDpath = ft_strnstr(envp1[i], "PATH", 4);
		if (allpathinoneDpath)
		{
			twoDpaths = ft_split(allpathinoneDpath + 5, ':');
			return (twoDpaths);
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

// char* if_executable(char* path,char** twoDpath)
// {
//     if(access(path,X_OK) == 0)
//     {
//         free_two_d_array(twoDpath);
//         return (path);
//     }
//     else
//         ft_printf("%s \n",strerror(errno));
//     return (NULL);
// }

// char* check_path(char** twoDpath,char* command_name)
// {
//     int i;
//     i = 0;
//     char* path;

//     while(twoDpath[i])
//     {
//         path = NULL;
//         path = concatenate_path(twoDpath[i],command_name);
//         if(access(path,F_OK) == 0)
//         {
//             free_two_d_array(twoDpath);
//             return (path);
//         }
//         else
//         {
//             free(path);
//         }
//         i++;
//     }

//     free_two_d_array(twoDpath);
//     return (NULL);
// }

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

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**av;
	char	*command_name;
	char	*pat;

	(void)argc;
	(void)envp;
	paths = extract_path(envp);
	if (!paths)
	{
		ft_printf("Error: PATH not found in the environment.\n");
		return (1);
	}
	av = ft_split(argv[1], ' ');
	command_name = av[0];
	pat = check_path(paths, command_name);
	free_two_d_array(av);
	if (!pat)
	{
		perror("there is no path: ");
	}
	ft_printf("%s\n", pat);
	exit(1);
	return (0);
}

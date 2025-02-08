/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:28:06 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/08 18:48:25 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*check_command(char *path, char **twoDpath)
{
	if (access(path, X_OK | F_OK) == 0)
	{
		dprintf(2,"up\n");
		free_two_d_array(twoDpath);
		return (path);
	}
	//else if (access(path, F_OK) != 0)
	//{
	//	return ("no such file or directory");
	//}
	//else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	//{
	//	free_two_d_array(twoDpath);
	//	return ("permission denied");
	//}
	return NULL;
}

char	*check_path(char **twoDpath, char *command_name)
{
	int		i;
	char	*path;
	char	*result;

	i = 0;
	path = NULL;
	if (ft_strchr(command_name, '/') != 0 && access(command_name,
			F_OK | X_OK) != -1)
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

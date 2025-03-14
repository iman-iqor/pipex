/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:14:42 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/12 23:31:23 by imiqor           ###   ########.fr       */
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

char	*check_path(char **twoDpath, char *command_name, char **av)
{
	int		i;
	char	*path;
	char	*result;

	i = 0;
	path = NULL;
	if (ft_strchr(command_name, '/'))
		return (ft_strdup(command_name));
	else if (!twoDpath)
	{
		ft_putstr("command", " not found\n");
		free_two_d_array(av);
		exit(EXIT_FAILURE);
	}
	while (twoDpath[i])
	{
		path = concatenate_path(twoDpath[i], command_name);
		result = check_command(path);
		if (result)
			return (result);
		free(path);
		i++;
	}
	return (command_name);
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

char	*check_command(char *path)
{
	if (access(path, F_OK) == 0)
	{
		return (path);
	}
	return (NULL);
}

void	ft_putstr(char *s1, char *s2)
{
	if (!s1)
		write(2, "(null)", 6);
	else
		write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:28:38 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/09 19:02:12 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_fprintf/ft_fprintf.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

int		setup_and_execute(int argc, char **argv, char **envp);
char	**extract_path(char **envp1);
char	*concatenate_path(char *oneDfromthetwoDpath, char *command_name);
void	free_two_d_array(char **arr);
char	*check_command(char *path);
char	*check_path(char **twoDpath, char *command_name);
int		open_file_for_reading(char *filename, char **env);
int		open_file_for_writing(char *filename, char **env);
void	execute_command(char *cmd, char **env, char **envp);
void	handle_first_child(int *fd, char **argv, char **env, char **envp);
void	handle_second_child(int *fd, char **argv, char **env, char **envp);
int		ft_execve(char *exact_path, char **av, char **envp);
#endif

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include "../ft_fprintf/ft_fprintf.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*concatenate_path(char *oneDfromthetwoDpath, char *command_name);
char	*check_path(char **twoDpath, char *command_name);
char	**extract_path(char **envp1);
char	*check_command(char *path, char **twoDpath, char *o);
void	execute_command(char *cmd, char **env, char **envp);
void	free_two_d_array(char **arr);
void	check_pipe_is_valid(int pipe_return);
void	dup2_and_close_pipe_fds(int fd1, int fd2, int mode);
void	dup2_and_close_file_fd(int fd, int mode);
int	open_input_file(char *filename,char** env);
int	open_output_file(char *filename,char** env);
void	check_fork(int fork_ret, char **env);

#endif
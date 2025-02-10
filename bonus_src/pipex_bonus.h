/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imiqor <imiqor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:17:07 by imiqor            #+#    #+#             */
/*   Updated: 2025/02/10 15:10:07 by imiqor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../ft_fprintf/ft_fprintf.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "./m/get_next_line_bonus.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_state
{
	int		i;
	int		fd[2];
	int		pid;
	int		fd1;
	char	**env;
}			t_state;

char		*concatenate_path(char *oneDfromthetwoDpath, char *command_name);
char		*check_path(char **twoDpath_env, char *command_name);
char		**extract_path(char **envp1);
char		*check_command(char *path);
void		execute_command(char *cmd, char **env, char **envp);
void		free_two_d_array(char **arr);
void		check_pipe_is_valid(int pipe_return);
void		dup2_and_close_pipe_fds(int fd1, int fd2, int mode);
void		dup2_and_close_file_fd(int fd, int mode);
int			open_input_file(char *file, char *filename, char **env);
int			open_output_file(char *filename, char **env);
void		check_fork(int fork_ret, char **env);
void		check_argc(int argc, char **argv);
void		wait_all_pipex(void);
void		init_state(t_state *state, int argc, char **argv, char **envp);
void		in_parent(t_state state, int *in_fd);
void		child(t_state state, int argc, char **argv, char **envp);

int			open_output_filee_here_doc_util(char *filename, char **env);
void		handle_first_child(int *fd, char **argv, char **env, char **envp);
void		handle_second_child(int *fd, char **argv, char **env, char **envp);
int			ft_strcmp(char *str1, char *str2);
int			here_doc_exist(char *argv1);
char		*here_doc_wih_get_next_line(char *argv1, char *argv2);
void		pipe_is_valid(int pipe_return);
void		fork_is_valid(int fork_return);
void		close_and_dup2_pipe_fds(int fd1, int fd2, int mode);
int			setup_and_execute(char **argv, char **envp);
int			ft_pipe_and_fork(char **argv, char **envp);
int			ft_execve(char *exact_path, char **av, char **envp);
void		ft_putstr(char *s1, char *s2);
#endif
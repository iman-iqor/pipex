#include "./m/get_next_line_bonus.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../ft_fprintf/ft_fprintf.h"
#include "pipex_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int open_output_filee_here_doc_util(char *filename, char **env)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		free_two_d_array(env);
		perror(filename);
	}
	return (fd);
}
void handle_first_child(int *fd, char **argv, char **env, char **envp)
{
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execute_command(argv[3], env, envp);
}

void handle_second_child(int *fd, char **argv, char **env, char **envp)
{
    int f2;

    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    f2 = open_output_filee_here_doc_util(argv[5], env);
    dup2(f2, 1);
    close(f2);
    execute_command(argv[4], env, envp);

}

int ft_strcmp(char *str1, char *str2)
{
    int i;
    i = 0;
    if (!str1 || !str2)
        return -1;
    while (str1[i] && str2[i] && str1[i] == str2[i])
    {
        i++;
    }
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}
int here_doc_exist(char *argv1)
{
    if (ft_strcmp(argv1, "here_doc") == 0)
        return 1;
    return 0;
}

char *here_doc_wih_get_next_line(char *argv1, char *argv2)
{
    char *buffer;
    char *s;
    int str_cmp_return;
    
    buffer = NULL;
    s = NULL;
    argv2 = ft_strjoin(argv2, "\n");
    if (here_doc_exist(argv1))
    {
        str_cmp_return = 1;
        while (str_cmp_return != 0)
        {
            s = get_next_line(0);
            str_cmp_return = ft_strcmp(s, argv2);
            if (str_cmp_return != 0)
                buffer = ft_sstrjoin(buffer, s);
            free(s);
        }
        free(argv2);
        get_next_line(-1);
        return buffer;
    }
    return NULL;
}
void pipe_is_valid(int pipe_return)
{
    if (pipe_return == -1)
    {
        ft_fprintf(2, "pipe failed\n");
        exit(-1);
    }
}
\
void fork_is_valid(int fork_return)
{
    if (fork_return == -1)
    {
        ft_fprintf(2, "fork failed\n");
        exit(-1);
    }
}
void close_and_dup2_pipe_fds(int fd1, int fd2, int mode)
{
    close(fd1);
    dup2(fd2, mode);
    close(fd2);
}

int setup_and_execute(int argc, char **argv, char **envp)
{
    int fd[2];
    char **env;

    int(pid1), (pid2);
    pipe_is_valid(pipe(fd));
    env = extract_path(envp);
    pid1 = fork();
    if (pid1 == 0)
        handle_first_child(fd, argv, env, envp);
    pid2 = fork();
    if (pid2 == 0)
        handle_second_child(fd, argv, env, envp);
    free_two_d_array(env);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}

void ft_pipe_and_fork(char **argv, int argc, char **envp)
{
    char *str;
    int fd[2];
    int pid;

    str = here_doc_wih_get_next_line(argv[1], argv[2]);
    pipe_is_valid(pipe(fd));
    write(fd[1], str, ft_strlen(str));
    free(str);
    //ft_printf("%s", str);
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);
    setup_and_execute(argc, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
    ft_pipe_and_fork(argv, argc, envp);
}

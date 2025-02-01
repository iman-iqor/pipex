
#include <stdio.h>
#include "./m/get_next_line_bonus.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../ft_fprintf/ft_fprintf.h"
#include<unistd.h>
#include<sys/wait.h>

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
    buffer = NULL;
    char *s;
    s = NULL;
    int str_cmp_return;
    argv2 = ft_strjoin(argv2, "\n");
    if (here_doc_exist(argv1))
    {
        str_cmp_return = 1;
        while (str_cmp_return != 0)
        {
            s = get_next_line(0);
            str_cmp_return = ft_strcmp(s, argv2);
            if (str_cmp_return != 0)
                buffer = ft_strjoin(buffer, s);
        }
        return buffer;
    }
    return NULL;
}
void pipe_is_valid(int pipe_return)
{
	if(pipe_return == -1)
	{
		ft_fprintf(2,"pipe failed\n");
		exit(-1);
	}
}

void fork_is_valid(int fork_return)
{
	if(fork_return == -1)
	{
		ft_fprintf(2,"fork failed\n");
		exit(-1);
	}
}
void close_and_dup2_pipe_fds(int fd1,int fd2,int mode)
{
	close(fd1);
	dup2(fd2,mode);
	close(fd2);
}
void ft_pipe_and_fork(char **argv)
{
    char *str;
    int fd[2];
    int pid;
	char buff[11];


    str = here_doc_wih_get_next_line(argv[1], argv[2]);
    pipe_is_valid(pipe(fd));
    pid  = fork();
	fork_is_valid(pid);
    if(pid == 0)
    {
		close_and_dup2_pipe_fds(fd[0],fd[1],1);
		ft_printf("%s",str);
    }

	close(fd[1]);
	read(fd[0], buff, 10);

	waitpid(pid,NULL,0);

	printf("%s",buff);

}

int main(int argc, char **argv)
{

    //printf("%s",ft_pipe_and_fork(argv));
	ft_pipe_and_fork(argv);
}

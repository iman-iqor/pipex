#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include "libft/libft.h"
#include "ft_fprintf/ft_fprintf.h"
#include "ft_printf/ft_printf.h"



int main(int argc,char**argv,char** envp)
{
    int fd[2];
    //char buffer[100], buffer2[100];
    int pid1, pid2;
    pipe(fd);
    char *env[] = {"/usr/bin", NULL};

    pid1 = fork();
    (void)envp;
    (void)argc;
    if(pid1 == 0)
    {
        close(fd[0]);
        if(access(argv[1], F_OK | R_OK) == 0)
        {
            int f = open(argv[1], O_RDONLY);
            dup2(f,0);
            close(f);
        }
        else
            ft_printf("access failed\n");


        char **av = ft_split(argv[2], ' ');

        dup2(fd[1] , 1);
        close(fd[1]);

        int ret = execve(av[0],av,env);
        if (ret == -1)
            ft_fprintf(fd[1],"%d",ret);
    }

    pid2 = fork();
    if(pid2 == 0)
    {
        
        close(fd[1]);
        char **av = ft_split(argv[3], ' ');
        ///read(fd[0], buffer2, sizeof(buffer2));
       
        
        if(access(argv[4] ,F_OK | W_OK) == 0)
        {
            int fd = open(argv[4], O_WRONLY);
            dup2(fd,1);
            close(fd);
        }
         else
            ft_printf("access failed\n");
        

        dup2(fd[0] , 0);
        close(fd[0]);
        int ret = execve(av[0],av,env);
        if (ret == -1)
            ft_fprintf(fd[1],"%d",ret);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 1);
    waitpid(pid2, NULL, 1);
}


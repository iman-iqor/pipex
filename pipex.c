#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include "libft/libft.h"
#include "ft_fprintf/ft_fprintf.h"
#include "ft_printf/ft_printf.h"




char** extract_path(char** envp1)
{
    int i = 0;
    char* allpathinoneDpath;
    char** twoDpaths;
    while(envp1[i])
    {
        allpathinoneDpath = ft_strnstr(envp1[i],"PATH",4);
        if(allpathinoneDpath)
        {
            twoDpaths = ft_split(allpathinoneDpath+5,':');
            return twoDpaths;
        }
        i++;
    }
    return NULL;
}
char* concatenate_path(char*oneDfromthetwoDpath,char* command_name)
{
    
    char* path;
    char* full_path;
    path = NULL;
    full_path = NULL;
    if(!oneDfromthetwoDpath)
        return NULL;
   
    path = ft_strjoin(oneDfromthetwoDpath,"/");
    
    full_path = ft_strjoin(path,command_name);
    
    free(path);
    return full_path;
}


void free_two_d_array(char** arr)
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
//         return path;
//     }
//     else
//         ft_printf("%s \n",strerror(errno));
//     return NULL;
// }




char* check_path(char** twoDpath,char* command_name)
{
    int i;
    i = 0;
    char* path;
    
    while(twoDpath[i])
    {
        path = NULL;
        path = concatenate_path(twoDpath[i],command_name);
        if(access(path,F_OK) == 0)
        {
            free_two_d_array(twoDpath);
            return path;
        }
        else
        {
            free(path);
        }
        i++;
    }

    free_two_d_array(twoDpath);
    return NULL;
}

int main(int argc,char**argv,char** envp)
{
    int fd[2];
    int pid1, pid2;
    (void)envp;
    
    if(pipe(fd) == -1) 
    {
        perror("pipe:");
        return -1;
    }
    if(argc <=4)
    {
        ft_printf("pipe usage:program name + file1.txt + cmd1 + cmd2 + file2.txt  at  least in the mandatory");
        return 1;
    }





    char *env[] = {"/usr/bin", NULL};

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
        if (!av) {
            perror("ft_split error");
                return 1;
        }

        if (execve(av[0],av,env) == -1)
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
        
        if (execve(av[0],av,env) == -1)
        {
            perror("cmd2 error:");
            return 1;
        }
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 1);
    waitpid(pid2, NULL, 1);
}


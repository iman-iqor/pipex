#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
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
    path = NULL;
    if(!oneDfromthetwoDpath)
        return NULL;
   
    path = ft_strjoin(oneDfromthetwoDpath,"/");
    
    path = ft_strjoin(path,command_name);
    
    return path;
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


int main(int argc, char** argv , char** envp)
{/*  */
    (void)argc;
    (void)envp;

    char** paths = extract_path(envp);
    char**av = ft_split(argv[1],' ');
    char* command_name = av[0];
    char* pat=check_path(paths,command_name);
    if(pat)
        ft_printf("%s\n",pat);
    return 0;
}
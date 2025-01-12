#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "ft_fprintf/ft_fprintf.h"
#include "ft_printf/ft_printf.h"

int main(int argc, char **argv, char **envp)
{
    int fd[2]; // Pipe for communication between the two child processes
    int pid1, pid2;

    if (argc < 4) // Ensure at least 3 arguments are provided
    {
        ft_printf("Usage: ./program file1 cmd1 cmd2\n");
        return 1;
    }

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid1 = fork();
    if (pid1 == 0) // First child process
    {
        close(fd[0]); // Close unused read-end of the pipe
        int f = open(argv[1], O_RDONLY);
        if (f < 0)
        {
            perror("open file1");
            return 1;
        }
        dup2(f, STDIN_FILENO); // Redirect file1 to stdin
        close(f);

        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe write-end
        close(fd[1]);

        char **av1 = ft_split(argv[2], ' '); // Split cmd1
        if (execve(av1[0], av1, envp) == -1)
        {
            perror("execve cmd1");
            return 1;
        }
    }

    pid2 = fork();
    if (pid2 == 0) // Second child process
    {
        close(fd[1]); // Close unused write-end of the pipe
        dup2(fd[0], STDIN_FILENO); // Redirect pipe read-end to stdin
        close(fd[0]);

        char **av2 = ft_split(argv[3], ' '); // Split cmd2
        if (execve(av2[0], av2, envp) == -1)
        {
            perror("execve cmd2");
            return 1;
        }
    }

    // Parent process
    close(fd[0]); // Close both ends of the pipe
    close(fd[1]);
    waitpid(pid1, NULL, 0); // Wait for the first child
    waitpid(pid2, NULL, 0); // Wait for the second child

    return 0;
}

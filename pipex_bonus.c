#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// Error handling
void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Open files for input and output
void open_files(char *infile_name, char *outfile_name, int *infile, int *outfile) {
    *infile = open(infile_name, O_RDONLY);
    if (*infile < 0) handle_error("open infile");
    *outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*outfile < 0) handle_error("open outfile");
}

// Create pipes
void create_pipes(int *pipes, int pipe_count) {
    for (int i = 0; i < pipe_count; i++) {
        if (pipe(&pipes[2 * i]) == -1) {
            handle_error("pipe");
        }
    }
}

// Set up redirections for child process
void setup_redirection(int i, int cmd_count, int *pipes, int infile, int outfile) {
    if (i == 0) {
        dup2(infile, STDIN_FILENO);
    } else {
        dup2(pipes[2 * (i - 1)], STDIN_FILENO);
    }

    if (i == cmd_count - 1) {
        dup2(outfile, STDOUT_FILENO);
    } else {
        dup2(pipes[2 * i + 1], STDOUT_FILENO);
    }
}

// Close all pipe ends
void close_pipes(int *pipes, int pipe_count) {
    for (int i = 0; i < 2 * pipe_count; i++) {
        close(pipes[i]);
    }
}

// Execute commands
void execute_command(int i, int cmd_count, int *pipes, char **cmds, char **envp, int infile, int outfile) {
    setup_redirection(i, cmd_count, pipes, infile, outfile);
    close_pipes(pipes, cmd_count - 1);
    char *args[] = {cmds[i], NULL};
    if (execve(cmds[i], args, envp) == -1) {
        handle_error("execve");
    }
}

int main(int argc, char **argv, char **envp) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s infile cmd1 cmd2 ... cmdN outfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    int cmd_count = argc - 3;
    int pipes[2 * (cmd_count - 1)];
    int infile, outfile;

    open_files(argv[1], argv[argc - 1], &infile, &outfile);
    create_pipes(pipes, cmd_count - 1);

    for (int i = 0; i < cmd_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execute_command(i, cmd_count, pipes, &argv[2], envp, infile, outfile);
        }
    }

    close_pipes(pipes, cmd_count - 1);
    close(infile);
    close(outfile);

    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}


# Pipex 🚀

## About 💡
**Pipex** is a C project that replicates the behavior of piping commands in Unix, where the output of one command becomes the input of another, all through a pipe mechanism. This project simulates the shell command `< file1 cmd1 | cmd2 > file2`, helping you learn about **pipes**, **forking**, and **execve**.


Replicates commands like:
```bash
$> ./pipex infile "ls -l" "wc -l" outfile
Behaves like:
< infile ls -l | wc -l > outfile
Features ✨

    Handle single pipes: cmd1 | cmd2
    Handle multiple pipes: cmd1 | cmd2 | cmd3
    Handle file input/output using files: < file1 ... > file2
**************************************************************************************
Bonus 💎

    Multiple pipes: cmd1 | cmd2 | cmd3 | ...
    Here document: here_doc LIMITER cmd cmd1 file → cmd << LIMITER | cmd1 >> file
***********************************************************************************
Installation ⚡

Clone this repo:
git clone https://github.com/iman-iqor/pipex.git
Make sure to compile using the provided Makefile:
make
Usage 🔥

Run the program as follows:
./pipex infile "cmd1" "cmd2" outfile
**********************************************************************************************
Requirements 📋

    C programming language
    Must comply with the Norm ✍️
    No segmentation faults, bus errors, or memory leaks 🚫
    External functions: open, close, fork, execve, pipe, etc.
    Use of libft library allowed!
********************************************************************************************
Author ✨

Developed by [iman iqor] 👩‍💻

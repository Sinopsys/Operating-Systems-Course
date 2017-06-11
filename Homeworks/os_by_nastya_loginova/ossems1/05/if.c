#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

   

    int pipe_fd1[2];
    int pipe_fd2[2];
    pid_t ls_pid, grep_pid;

    pipe(pipe_fd1);

    ls_pid = fork();
    if (ls_pid == 0) { //first child ls DIR -laR
        dup2(pipe_fd1[1], STDOUT_FILENO);
        close(pipe_fd1[0]);
        execlp("ls", "ls", argv[1], "-laR", NULL);

    } else if (ls_pid > 0) {
        dup2(pipe_fd1[0], STDIN_FILENO);
        close(pipe_fd1[1]);

        pipe(pipe_fd2);
        grep_pid = fork();

        if (grep_pid == 0) { //second child grep ARG
            dup2(pipe_fd2[1], STDOUT_FILENO);
            close(pipe_fd2[0]);  
            execlp("grep", "grep", argv[2], NULL);

        } else if (grep_pid > 0) { //parent sort
            dup2(pipe_fd2[0], STDIN_FILENO);
            close(pipe_fd2[1]);
            execlp("sort", "sort", NULL);
        }

    }

    return 0;
}


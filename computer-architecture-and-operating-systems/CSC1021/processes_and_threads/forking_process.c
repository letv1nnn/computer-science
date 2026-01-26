#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    
    printf("[parent process] - start (PID: %d)\n", getpid());
    pid_t pid;

    pid = fork();

    /* The parent gets the child PID, and the child PID gets 0. */

    if (pid < 0) {                          /* error occured */
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } else if (pid == 0) {                  /* child process */
        printf("[child process] - start (CURRENT PID: %d, PARENT PID: %d)\n", getpid(), getppid());
        execlp("/bin/ls", "ls", NULL);
    } else {                                /* parent process */
        pid_t pid  = wait(NULL);  /* parent will wait for the child to complete */
        printf("[child process] - complete, PID: %d\n", pid);
    }
    
    printf("[parent process] - completing... (PID: %d)\n", getpid());

    return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    for (size_t i = 1; i < argc; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
        } else if (pid == 0) {
#ifdef DEBUG
            printf("[child process] - %d, [parent process] - %d\n", getpid(), getppid());
#endif
            const char *filepath = argv[i];
            execlp("wc", "wc", "-l", filepath, NULL); 
            perror("execlp failed");
            _exit(1);
        }
    }
#ifdef DEBUG
        printf("[parent process] - %d\n", getpid());
#endif
    for (size_t i = 0; i < argc - 1; ++i)
        wait(NULL);
 
    return 0;
}


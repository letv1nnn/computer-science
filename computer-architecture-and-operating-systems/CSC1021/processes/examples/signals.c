#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed");
    } else if (pid == 0) {
        for (int i = 0; i < 10; ++i) {
            sleep(3);
            printf("[child %d] iteration = %d\n", getpid(), i);
        }
    } else {
        printf("[parent %d] enter `1` to kill the child\n", getpid());
        int input;
        int serr = scanf("%d", &input);
        if (serr != 1) {
            fprintf(stderr, "scanf failed");
        }
        if (serr == 1) {
            kill(pid, SIGTERM);
        }
    }

    return 0;
}

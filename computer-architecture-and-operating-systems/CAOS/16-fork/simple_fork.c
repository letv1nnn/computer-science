#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    printf("I'm printed once\n");

    pid_t pid = fork();

    while (1) {
        printf("[%d] pid returned after fork: %d, parent pid: %d\n", getpid(), pid, getppid());
        sleep(100);
    }

    return 0;
}

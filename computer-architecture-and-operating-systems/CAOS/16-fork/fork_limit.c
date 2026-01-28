#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int counter = 1;
    pid_t pid = 0;

    while (!pid) {
        if ((pid = fork()) != -1) {
            counter++;
        } else {
            perror("fork failed");
        }
    }

    if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else if (pid != -1) {
        printf("%d\n", counter);
        _exit(0);
    }

    return 0;
}

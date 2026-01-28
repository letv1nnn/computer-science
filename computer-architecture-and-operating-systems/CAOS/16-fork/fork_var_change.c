#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int x = 100;

    pid_t pid = fork();

    if (pid == 0) {
        printf("[Child] x = %d (addr: %p)\n", x, &x);
        x = 1000;
        printf("[Child] x = %d (addr: %p)\n", x, &x);
        _exit(0);
    }

    sleep(5);

    printf("[Parent] x = %d (addr: %p)\n", x, &x);

    return 0;
}

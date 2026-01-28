#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int child_function() {
    sleep(2);
    printf("[child][%d] running\n", getpid());
    _exit(0);
}

int main(int argc, char **argv) {
    int child_num = 5;

    for (int i = 0; i < child_num; ++i)
        if (fork() == 0)
            child_function();

    for (int i = 0; i < child_num; ++i)
        wait(NULL);

    printf("[parent] all processes finished\n");

    return 0;
}

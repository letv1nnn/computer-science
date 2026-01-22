#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *hello_world(void *arg) {
    (void)(arg);
    printf("Hello, Multithreading World!\n");
    return (void *)0;
}

int main(int argc, char **argv) {
    pthread_t th;
    int exit_code = 0;

    exit_code = pthread_create(&th, NULL, &hello_world, NULL);
    if (exit_code != 0) return exit_code;

    exit_code = pthread_join(th, NULL);
    if (exit_code != 0) return exit_code;

    return exit_code;
}

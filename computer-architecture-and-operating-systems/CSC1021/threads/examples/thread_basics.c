#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int shared = 0;

void *writer(void *arg) {
    sleep(1);
    shared = 42;
    printf("[writer thread] - set shared to %d\n", shared);
    return NULL;
}

void *reader(void *arg) {
    printf("[reader thread] - initial shared is %d\n", shared);

    while (shared == 0) {
        // busy wait
    }

    printf("[reader thread] - shared changed to %d\n", shared);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t t1, t2; 

    pthread_create(&t1, NULL, reader, NULL);
    pthread_create(&t2, NULL, writer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

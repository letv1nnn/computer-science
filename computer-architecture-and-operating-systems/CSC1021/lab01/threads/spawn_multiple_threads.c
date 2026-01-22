#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t input;
    uint64_t output;
} thread_data_t;

void *factorial(void *);
void factorial_tests(void);

int main(int argc, char **argv) {
    
    printf("Enter the number of threads: ");
    uint16_t number_of_threads;
    if (scanf("%hu", &number_of_threads) != 1) {
        fprintf(stderr, "Scanf failed!\n");
        return EXIT_FAILURE;
    }

    pthread_t *threads = (pthread_t *)malloc(number_of_threads * sizeof(pthread_t));
    thread_data_t *data = (thread_data_t *)malloc(number_of_threads * sizeof(thread_data_t));
    
    if (!threads || !data) {
        perror("memory allocation failed");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < number_of_threads; ++i) {
        data[i].input = i + 1;

        int err = pthread_create(threads + i, NULL, factorial, data + i);
        if (err != 0) {
            strerror(err);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < number_of_threads; ++i) {
        int err = pthread_join(threads[i], NULL);
        if (err != 0) {
            strerror(err);
            continue;
        }
        printf("factorial(%lu) = %lu\n", data[i].input, data[i].output);
    }

    free(threads);
    free(data);
    return EXIT_SUCCESS;
}

void *factorial(void *arg) {
    thread_data_t *data = arg;

    uint64_t n = data->input;
    uint64_t res = 1;

    for (size_t i = 1; i <= n; ++i) res *= i;

    data->output = res;
    return NULL;
}


#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    bool *sieve;
    bool is_allocated;
    int size;
} Sieve;

static Sieve sieve = {NULL, false, 0};

void create_sieve(const int size);
void build_sieve(void);
bool is_prime(int n);

int main(int argc, char **argv) {
    int number;
    if (argc == 2)
        number = atoi(argv[1]);
    else {
        printf("number: ");
        int sf = scanf("%d", &number);
        if (sf != 1) {
            perror("scanf failed, only integers valid");
            return 1;
        }
    }

    bool res = is_prime(number);
    if (res) printf("Given number is prime.\n");
    else printf("Given number is not prime.\n");

    free(sieve.sieve);
    sieve.sieve = NULL;
    sieve.size = 0;
    sieve.is_allocated = false;
    return 0;
}

void build_sieve() {
    sieve.sieve[0] = sieve.sieve[1] = false;
    int limit = (int)sqrt(sieve.size - 1);
    for (int i = 2; i <= limit; ++i) {
        if (sieve.sieve[i]) {
            for (int j = i * i; j < sieve.size; j+= i)
                sieve.sieve[j] = false;
        }
    }
}

void create_sieve(const int size) {
    if (!sieve.is_allocated) {
        sieve.size = size;
        sieve.sieve = (bool *)calloc(sieve.size, sizeof(bool));
        if (!sieve.sieve) {
            perror("memory allocation failed");
            return;
        }
        for (int i = 0; i < sieve.size; i++)
            sieve.sieve[i] = true;
        sieve.is_allocated = true;
    } else {
        bool *tmp = (bool *)realloc(sieve.sieve, sizeof(bool) * size);
        if (!tmp) {
            perror("memory allocation failed");
            return;
        }
        sieve.sieve = tmp;
        for (int i = sieve.size; i < size; i++)
            sieve.sieve[i] = true;
        sieve.size = size;
    }
    build_sieve();
}

bool is_prime(int n) {
    if (n < 2) return false;
    if (n >= sieve.size)
        create_sieve(n + 1);
    return sieve.sieve[n];
}

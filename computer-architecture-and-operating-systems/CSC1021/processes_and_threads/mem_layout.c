#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static char bss_segment;
static long long data_segment = 42;

int main(int argc, char **argv) {
    char *str = (char *)calloc(5, sizeof(char));
    int num = 0x0DDC0FFEE;

    printf("-------------------------------------0x00000000\n");
    printf("Data segment: %p\n", &data_segment);
    printf("BSS: %p\n", &bss_segment);
    printf("HEAP segment: %p\n", str);
    printf("STACK segment: %p\n", &num);
    printf("arg, environment segment: %p\n", argv);
    printf("-------------------------------------0x80000000\n");

    assert((long long *)&data_segment < (long long *)&bss_segment < (long long *)str < (long long *)&num < (long long *)argv);

    free(str);
    return 0;
}

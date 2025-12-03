#include <stddef.h>
#include <xmmintrin.h>
#include <stdlib.h>

__attribute__((noinline)) void vadd(float *a, float *b, size_t size) {
    size_t i;
    for (i = 0; i < size; i += 4) {
        __m128 v1 = _mm_load_ps(a + i);
        __m128 v2 = _mm_load_ps(b + i);
        __m128 v3 = _mm_add_ps(v1, v2);
        _mm_store_ps(a + i, v3);
    }
}

__attribute((noinline)) void sadd(float *a, float *b, size_t size) {
    size_t i;
    for (i = 0; i < size; i++)
        a[i] += b[i];
}

int main(void) {
    size_t size = 300000000;
    float *a = (float *)calloc(size, sizeof(float));
    float *b = (float *)calloc(size, sizeof(float));

    vadd(a, b, size);
    sadd(a, b, size);

    return 0;
}


// MIPT (2023-2024), seminar 5.2
// duff device

#include <assert.h>

void copy(int *, int *, int);

int main(int argc, char **argv) {
    int n = 9;
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, a2[n];

    copy(a2, a1, n);
    
    for (int i = 0; i < n; ++i)
        assert(a1[i] == a2[i]);

    return 0;
}

void copy(int *to, int *from, int count) {
    int n = (count + 3) / 4;
    switch (count % 4) {
        case 0: do { *to++ = *from++;
        case 3:      *to++ = *from++;
        case 2:      *to++ = *from++;
        case 1:      *to++ = *from++;
                } while (--n > 0);
    }
}

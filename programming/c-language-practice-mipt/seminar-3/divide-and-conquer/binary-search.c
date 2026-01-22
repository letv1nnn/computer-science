// MIPT (2023-2024), seminar 3.2

#include <stddef.h>
#include <assert.h>

typedef int (*cmp_t)(void const *lhs, void const *rhs);

int int_cmp(void const *lhs, void const *rhs); 
int char_cmp(void const *lhs, void const *rhs);

void *binary_search(void const *key, void const *base, int num, int n, cmp_t cpm);

int main(int argc, char **argv) {
    int arr_int[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
    char arr_char[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    int n_int = sizeof(arr_int) / sizeof(arr_int[0]), n_char = sizeof(arr_char) / sizeof(arr_char[0]);

    int key_int = 34;
    char key_char = 'G';

    assert(*((int *)binary_search(&key_int, arr_int, sizeof(int), n_int, int_cmp)) == 34);
    key_int = 128;
    assert(binary_search(&key_int, arr_int, sizeof(int), n_int, int_cmp) == NULL);
    
    assert(*((char *)binary_search(&key_char, arr_char, sizeof(char), n_char, char_cmp)) == 'G');
    key_char = 'P';
    assert(binary_search(&key_char, arr_char, sizeof(char), n_char, char_cmp) == NULL);
    
    return 0;
}

void *binary_search(void const *key, void const *base, int num, int n, cmp_t cmp) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left  + right) / 2;
        void const *mid_el = (char const *)base + mid * num;
        int result = cmp(key, mid_el);
        if (result == 0) return (void *)mid_el;
        else if (result < 0) right = mid - 1;
        else left = mid + 1;
    }
    return NULL;
}

int int_cmp(void const *lhs, void const *rhs) {
    int const *ilhs = (int const *)lhs;
    int const *irhs = (int const *)rhs;
    if (*ilhs == *irhs) return 0;
    else if (*ilhs > *irhs) return 1;
    return -1;
} 

int char_cmp(void const *lhs, void const *rhs) {
    char const *clhs = (char const *)lhs;
    char const *crhs = (char const *)rhs;
    if (*clhs == *crhs) return 0;
    else if (*clhs > *crhs) return 1;
    return -1;
}

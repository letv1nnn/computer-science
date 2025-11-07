// MIPT (2023-2024), seminar 3.2

#include <stdio.h>
#include <stdlib.h>

int int_cmp(const void *lhs, const void *rhs);
void print_int_array(int *arr, int n);

int main(int argc, char **argv) {
    int arr[] = {8, 3, 5, 9, 0, 1, 7, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_int_array(arr, n);
    qsort(arr, n, sizeof(int), int_cmp);
    print_int_array(arr, n);

    return 0;
}

int int_cmp(const void *lhs, const void *rhs) {
    const int *ilhs = (const int *)lhs;
    const int *irhs = (const int *)rhs;
    if (*ilhs > *irhs) return 1;
    else if (*ilhs < *irhs) return -1;
    return 0;
}

void print_int_array(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (i < n - 1) printf("%d, ", arr[i]);
        else printf("%d\n", arr[i]);
    }
}

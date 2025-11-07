// MIPT (2023-2024), seminar 3.3

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void print_int_array(int const *arr, int const n);
void counting_sort(int *arr, int n);

int main(int argc, char **argv) {
    int *arr;
    int n;
    if (argc > 1 && atoi(argv[1]) == argc - 2) {
        n = atoi(argv[1]);
        arr = (int *)calloc(n, sizeof(int));
        if (!arr) {
            perror("memory allocation failed");
            return 1;
        }
        for (int i = 0; i < n; ++i)
            arr[i] = atoi(argv[2 + i]);
    } else {
        printf("array size: ");
        int sf = scanf("%d", &n);
        if (sf != 1) {
            perror("scanf failed, it only accepts integers");
            return 1; 
        }
        arr = (int *)calloc(n, sizeof(int));
        if (!arr) {
            perror("memory allocation failed");
            return 1;
        }

        printf("Enter array values\n");
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr + i);
        }
    }
    
    printf("Initial array: ");
    print_int_array(arr, n);

    counting_sort(arr, n);

    printf("Sorted array: ");
    print_int_array(arr, n);

    free(arr);
    return 0;
}

void print_int_array(int const *arr, int const n) {
    for (int i = 0; i < n; ++i) {
        if (i < n - 1)
            printf("%d, ", arr[i]);
        else
            printf("%d\n", arr[i]);
    }
}

void counting_sort(int *arr, int n) {
    if (n <= 0) return;

    int min_el = arr[0];
    int max_el = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < min_el) min_el = arr[i];
        if (arr[i] > max_el) max_el = arr[i];
    }

    int range = max_el - min_el + 1;

    int *counting_arr = (int *)calloc(range, sizeof(int));
    if (!counting_arr) {
        perror("memory allocation failed");
        return;
    }

    for (int i = 0; i < n; ++i)
        ++counting_arr[arr[i] - min_el];

    for (int i = 0, idx = 0; i < range; ++i)
        while (counting_arr[i]-- > 0)
            arr[idx++] = i + min_el;

    free(counting_arr);
}

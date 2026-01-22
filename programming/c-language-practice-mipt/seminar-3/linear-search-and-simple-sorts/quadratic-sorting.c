// MIPT (2023-2024), seminar 3.1

#define SS 0 // selection sort
#define IS 0 // insertion sort
#define BS 1 // bubble sort

#include <stdio.h>

void print_int_array(int *arr, int n);
void selection_sort(int *arr, int n);
void insertion_sort(int *arr, int n);
void bubble_sort(int *arr, int n);

int main(int argc, char **argv) {
    int arr[] = {6, 7, 4, 5, 9, 3, 8, 1, 2, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Initial array: ");
    print_int_array(arr, n);
#if SS    
    selection_sort(arr, n);
    printf("Selection sort: ");
    print_int_array(arr, n);
#endif
#if IS
    insertion_sort(arr, n);
    printf("Insertion sort: ");
    print_int_array(arr, n);
#endif
#if BS
    bubble_sort(arr, n);
    printf("Bubble sort: ");
    print_int_array(arr, n);
#endif
    return 0;
}

void insertion_sort(int *arr, int n) {
    if (!arr) return;
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void bubble_sort(int *arr, int n) {
    if (!arr) return;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void selection_sort(int *arr, int n) {
    if (!arr) return;
    for (int i = 0; i < n; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[min_idx] > arr[j]) min_idx = j;
        }
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

void print_int_array(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (i < n - 1) printf("%d, ", arr[i]);
        else printf("%d\n", arr[i]);
    }
}

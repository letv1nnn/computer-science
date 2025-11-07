// MIPT (2023-2024), seminar 3.2

#include <stdio.h>

unsigned partition(int *arr, unsigned left, unsigned right);
void qs_implementation(int *arr, unsigned left, unsigned right);
void quick_sort(int *arr, int n);
void print_int_array(int *arr, int n);

int main(int argc, char **argv) {
    int arr[] = {6, 1, 9, 3, 2, 8, 7, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_int_array(arr, n);    
    quick_sort(arr, n);
    print_int_array(arr, n);    

    return 0;
}

unsigned partition(int *arr, unsigned left, unsigned right) {
    int pivot = arr[left];
    int start = left;
    ++left;
    while (left <= right) {
        if (arr[left] < pivot) {
            ++left;
            continue;
        }
        if (arr[right] > pivot) {
            --right; 
            continue;
        }
        int tmp = arr[left]; arr[left] = arr[right]; arr[right] = tmp;
        ++left; --right;
    }
    int tmp = arr[start]; arr[start] = arr[right]; arr[right] = tmp;
    return right;
}

void qs_implementation(int *arr, unsigned left, unsigned right) {
    if (left >= right) return;
    unsigned p = partition(arr, left, right);
    qs_implementation(arr, left, p - 1);
    qs_implementation(arr, p + 1, right);
}

void quick_sort(int *arr, int n) {
    int left = 0, right = n - 1;
    qs_implementation(arr, left, right);
}

void print_int_array(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (i < n - 1) printf("%d, ", arr[i]);
        else printf("%d\n", arr[i]);
    }
}

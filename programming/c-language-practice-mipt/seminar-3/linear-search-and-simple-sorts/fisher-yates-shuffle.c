// MIPT (2023-2024), seminar 3.1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_int_array(int *arr, int n);
void fisher_yates_shuffle(int *arr, int n);

int main(int argc, char **argv) {
    srand(time(NULL));

    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_int_array(arr, n);
    fisher_yates_shuffle(arr, n);
    print_int_array(arr, n);
    
    return 0;
}

void fisher_yates_shuffle(int *arr, int n) {
    if (n < 2) return;
    for (int i = n - 1; i >= 0; --i) {
        // getting a random index between the first and the last - 1 value
        int random_index = rand() % (i + 1);
        // swapping the last and the random_value
        int tmp = arr[random_index];
        arr[random_index] = arr[i];
        arr[i] = tmp;
    }
}

void print_int_array(int *arr, int n) {
    if (!arr) return;
    for (int i = 0; i < n; ++i) {
        if (i < n - 1) printf("%d, ", arr[i]);
        else printf("%d\n", arr[i]);
    }
}

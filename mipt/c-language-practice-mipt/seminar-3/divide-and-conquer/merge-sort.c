// MIPT (2023-2024), seminar 3.2

#include <stdio.h>

void merge(int *arr, int left, int mid, int right);
void merge_sort(int *arr, int left, int right);
void display_array(int *arr, int n);

int main(int argc, char **argv) {
    int arr[] = {56, 12, 90, 34, 67, 22, 68, 23};    
    
    display_array(arr, 8);
    merge_sort(arr, 0, 7);
    display_array(arr, 8);

    return 0;
}

void merge(int *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        rightArr[i] = arr[mid + i + 1];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void merge_sort(int *arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

void display_array(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (i < n - 1) {
            printf("%d, ", arr[i]);
        } else {
            printf("%d\n", arr[i]);
        }
    }
}

#pragma once

#include <cstddef>

// helper functions
template<typename T>
void swap(T *a, T *b) { T tmp = *a; *a = *b; *b = tmp; }

// ==========================================================> divide and conquer sorting algorithms O(n * log(n))
template<typename T>
void merge(T *arr, size_t left, size_t mid, size_t right) {
    const size_t n1 = mid - left - 1, n2 = right - mid;
    T arr_left[n1], arr_right[n2];

    for (size_t i = 0; i < n1; ++i) arr_left[i] = arr[left + i];
    for (size_t i = 0; i < n2; ++i) arr_right[i] = arr[mid + i + 1];
    
    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (arr_left[i] < arr_right[j]) { arr[k] = arr_left[i]; i++; }
        else { arr[k] = arr_right[j]; j++; }
        ++k;
    }

    while (i < n1) { arr[k] = arr_left[i]; i++; k++; }
    while (j < n2) { arr[k] = arr_right[j]; j++; k++; }
}

template<typename T>
void ms_run(T *arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = (left + right) / 2;
        ms_run(arr, left, mid); ms_run(arr, mid + 1, right);
        merge(arr, left, mid, right);
    } 
}

template<typename T>
void merge_sort(T *arr, size_t size) { ms_run(arr, 0, size - 1); }

template<typename T>
size_t partition(T *arr, size_t left, size_t right) {
    T pivot = arr[left]; size_t start = left; left++;
    while (left <= right) {
        if (arr[left] < pivot) { ++left; continue; }
        if (arr[right] > pivot) { ++right; continue; }
        swap(arr + left, arr + right);
        ++left; --right;
    }
    swap(arr + start, arr + right);
    return right;
}

template<typename T>
void qs_run(T *arr, const size_t left, const size_t right) {
    if (left >= right) return;
    size_t pivot = partition(arr, left, right);
    qs_run(arr, left, pivot - 1);
    qs_run(arr, pivot + 1, right);
}

template<typename T>
void quick_sort(T *arr, const size_t size) { qs_run(arr, 0, size - 1); }


// ==========================================================> quadratic sorting algorithms O(N^2)
template<typename T>
void bubble_sort(T *array, const size_t size) {
    if (!array || size == 0 || size == 1) return;
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j)
            if (array[j] > array[j + 1]) swap(array + j, array + j + 1);
    }
}

template<typename T>
void insertion_sort(T *array, const size_t size) {
    if (!array || size == 0 || size == 1) return;
    for (int i = 1; i < size; ++i) {
        int key = array[i], j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    } 
}

template<typename T>
void selection_sort(T *array, const size_t size) {
    if (!array || size == 0 || size == 1) return;
    for (int i = 0; i < size; ++i) {
        int smallest_idx = i;
        for (int j = i + 1; j < size; ++j)
            if (array[j] < array[smallest_idx]) smallest_idx = j;
        swap(array + i, array + smallest_idx);
    }
}

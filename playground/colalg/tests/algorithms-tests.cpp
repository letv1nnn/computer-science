#include "../include/algorithms.hpp"
#include <assert.h>
#include <iostream>

#define TEST_HEADER(header) std::cout << "\t<===> TEST: " << (header) << " <===>\n";
#define TEST_PASSED(action) std::cout << "PASSED: " << (action) << '\n';
#define TEST_ALL_PASSED std::cout << "All tests PASSED ✅\n";

bool compare_arrays(int *a, const size_t as, int *b, const size_t bs) {
    if (as != bs) return false;
    for (int i = 0; i < as; ++i)
        if (a[i] != b[i]) return false;
    return true;
}

void bubble_sort_test();
void selection_sort_test();
void insertion_sort_test();
void quick_sort_test();
void merge_sort_test();

int main(int argc, char **argv) {
    TEST_HEADER("quadratic sorting algorithms");

    bubble_sort_test();
    selection_sort_test();
    insertion_sort_test();   
    merge_sort_test();
    quick_sort_test();

    TEST_ALL_PASSED;
    return 0;
}

void quick_sort_test() {
    int arr[] = {5, 1, 9, 3, 8, 2, 6, 4, 0, 7}; size_t size = 10;
    int sorted_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    quick_sort(arr, size); 
    assert(compare_arrays(arr, size, sorted_arr, size) == true);
    TEST_PASSED("quick sort");
}

void merge_sort_test() {
    int arr[] = {5, 1, 9, 3, 8, 2, 6, 4, 0, 7}; size_t size = 10;
    int sorted_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    merge_sort(arr, size); 
    assert(compare_arrays(arr, size, sorted_arr, size) == true);
    TEST_PASSED("merge sort");
}

void insertion_sort_test() {
    int arr[] = {5, 1, 9, 3, 8, 2, 6, 4, 0, 7}; size_t size = 10;
    int sorted_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    insertion_sort(arr, size); 
    assert(compare_arrays(arr, size, sorted_arr, size) == true);
    TEST_PASSED("insertion sort");
}

void selection_sort_test() {
    int arr[] = {5, 1, 9, 3, 8, 2, 6, 4, 0, 7}; size_t size = 10;
    int sorted_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    selection_sort(arr, size); 
    assert(compare_arrays(arr, size, sorted_arr, size) == true);
    TEST_PASSED("selection sort");
}

void bubble_sort_test() {
    int arr[] = {5, 1, 9, 3, 8, 2, 6, 4, 0, 7}; size_t size = 10;
    int sorted_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bubble_sort(arr, size);
    assert(compare_arrays(arr, size, sorted_arr, size) == true);
    TEST_PASSED("bubble sort");
}


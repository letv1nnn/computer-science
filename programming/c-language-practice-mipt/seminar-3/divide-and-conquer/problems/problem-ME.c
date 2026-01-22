// MIPT (2023-2024), seminar 3.2

#include <assert.h>

int majority_element_counting(int const *arr, unsigned n);
int majority_element_brute_force(int const *arr, unsigned n);

int main(int argc, char **argv) {
    int arr[] = {3, 2, 2, 3, 3, 5, 2, 2, 2, 6, 2};
    
    int x = majority_element_counting(arr, sizeof(arr) / sizeof(arr[0]));
    assert(x == 2);

    x = majority_element_brute_force(arr, sizeof(arr) / sizeof(arr[0]));
    assert(x == 2);

    return 0;
}

int majority_element_counting(int const *arr, unsigned n) {
    int m = arr[0], i = 0;
    for (int j = 1; j < n; ++j) {
        if (arr[j] != m && i == 0) m = arr[j];
        else if (arr[j] == m) ++i;
        else --i;
    }

    return m;
}

int majority_element_brute_force(int const *arr, unsigned n) {
    int majority = -1, res = -1;
    for (int i = 0; i < n; ++i) {
        int curr = 0;
        for (int j = 0; j < n; ++j) {
            if (arr[j] == arr[i]) ++curr;
        }
        if (curr > majority) {
            majority = curr;
            res = arr[i];
        } 
    }
    return res;
}

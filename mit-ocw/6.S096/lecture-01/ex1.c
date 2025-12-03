// MIT OCW 6.S096
// binary search example

#include <stddef.h>

size_t binary_search(int *data, size_t N, int value) {
    size_t l = 0, r = N - 1;
    
    while (l <= r) {
        size_t mid = l + (r - l) / 2; // avoiding possible overflow
        
        if (data[mid] < value) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return (r == l && data[l] == value) ? l : N;
}


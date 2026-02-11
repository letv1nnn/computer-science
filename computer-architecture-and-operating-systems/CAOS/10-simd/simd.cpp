// __m128  -> 128-bit register  -> 4 floats
// __m256  -> 256-bit register  -> 8 floats
// __m512  -> 512-bit register  -> 16 floats (AVX-512)
// e.g. __m128(_ - float, i - int, d - double)
//
// Aligned (faster, requires alignment):
//    _mm_load_ps(ptr)
//    _mm_store_ps(ptr, v)
//
// Unaligned (safe default):
//    _mm_loadu_ps(ptr)
//    _mm_storeu_ps(ptr, v)
//

#include <cassert>
#include <immintrin.h>
#include <array>
#include <chrono>
#include <iostream>
#include <xmmintrin.h>

#define PRINT_BENCH(STR, DUR) (std::cout << (STR) << ": " << (DUR.count()) << "ms\n")

template <std::size_t N>
void fill_array(std::array<float, N> &arr) {
    for (std::size_t i{}; i < N; ++i)
        arr[i] = static_cast<float>(i);
}

template <std::size_t N>
void add_arrays(const std::array<float, N> &a1, const std::array<float, N> &a2, std::array<float, N> &res) {
    for (std::size_t i{}; i < N; ++i) res[i] = a1[i] + a2[i];
}

template <std::size_t N>
void add_arrays_simd(const std::array<float, N> &a1, const std::array<float, N> &a2, std::array<float, N> &res) {
    std::size_t i{};
    for (; i <= N - 4; i += 4) {
        __m128 va = _mm_loadu_ps(&a1[i]), vb = _mm_loadu_ps(&a2[i]);
        __m128 vr = _mm_add_ps(va, vb);
        _mm_storeu_ps(&res[i], vr);
    }
    for (; i < N; ++i) res[i] = a1[i] + a2[i];
}

int main(int argc, char **argv) {
    constexpr std::size_t N = 100000;

    std::array<float, N> res1, res2, a1, a2;
    fill_array(a1); fill_array(a2);

    // scalar c++
    auto start = std::chrono::high_resolution_clock::now();
    add_arrays(a1, a2, res1); 
    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double, std::milli> duration = end - start;
    PRINT_BENCH("Scalar C++", duration);

    // leverage simd
    start = std::chrono::high_resolution_clock::now();
    add_arrays_simd(a1, a2, res2);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    PRINT_BENCH("SIMD C++", duration); 
    
    assert(res1 == res2); 
    
    return 0;
}

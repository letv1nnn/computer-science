#include <cuda_runtime.h>

__global__ void matrix_multiplication_kernel(const float* A, const float* B, float* C, int M, int N, int K) {
    std::size_t y{blockIdx.y * 16 + threadIdx.y}, x{blockIdx.x * 16 + threadIdx.x};
    if(x >= K || y >= M) return;
    
    std::size_t idx{K * y + x};
    C[idx] = 0.0;
    for (std::size_t i{}; i < N; ++i) {
        std::size_t ai{y * N + i}, bi{i * K + x};
        C[idx] += A[ai] * B[bi];
    }    
}

// A, B, C are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float* A, const float* B, float* C, int M, int N, int K) {
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((K + threadsPerBlock.x - 1) / threadsPerBlock.x,
                       (M + threadsPerBlock.y - 1) / threadsPerBlock.y);

    matrix_multiplication_kernel<<<blocksPerGrid, threadsPerBlock>>>(A, B, C, M, N, K);
    cudaDeviceSynchronize();
}

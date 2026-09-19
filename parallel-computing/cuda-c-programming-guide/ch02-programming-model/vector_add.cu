#include <iostream>
#include <cuda_runtime.h>

#define CUDA_CHECK(err) (cuda_check(err, __FILE__, __LINE__));

void cuda_check(const cudaError_t &err, const std::string &file, std::size_t line);

// kernel definition
__global__ void vec_add(const float *xs, const float *ys, float *out, std::size_t N) {
    std::size_t i{blockIdx.x * blockDim.x + threadIdx.x};
    if (i < N) out[i] = xs[i] + ys[i];
}

int main(int argc, char **argv) {
    constexpr std::size_t N{16};
    cudaError_t err;

    float xs[N], ys[N], out[N];
    for (std::size_t i{}; i < N; ++i) {
        xs[i] = static_cast<float>(i);
        ys[i] = 100.0f + static_cast<float>(i);
    }

    // gpu arrays
    float *d_xs, *d_ys, *d_out;

    err = cudaMalloc(&d_xs, N * sizeof(float));
    CUDA_CHECK(err);
    err = cudaMalloc(&d_ys, N * sizeof(float));
    CUDA_CHECK(err);
    err = cudaMalloc(&d_out, N * sizeof(float));
    CUDA_CHECK(err);

    // moving cpu arrays to gpu
    err = cudaMemcpy(d_xs, xs, N * sizeof(float), cudaMemcpyHostToDevice);
    CUDA_CHECK(err);
    err = cudaMemcpy(d_ys, ys, N * sizeof(float), cudaMemcpyHostToDevice);
    CUDA_CHECK(err);    

    // kernel invocation with 1 block and 16 threads
    vec_add<<<1, N>>>(d_xs, d_ys, d_out, N);

    err = cudaGetLastError();
    CUDA_CHECK(err);

    // moving `out` to cpu
    err = cudaMemcpy(out, d_out, N * sizeof(float), cudaMemcpyDeviceToHost);
    CUDA_CHECK(err);

    for (const auto& el : out)
        std::cout << el << '\n';

    cudaFree(d_xs);
    cudaFree(d_ys);
    cudaFree(d_out);

    return 0;
}

void cuda_check(const cudaError_t &err, const std::string &file, std::size_t line) {
    if (err != cudaSuccess) {
        std::cerr << "[CUDA ERROR] at file " << file << ":" << line << ":\n" << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}
#include "kernal/vector_add.hpp"
#include "cuda.cuh"

__global__ void kernal_vector_add(float *a, float *b, float *c, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        c[i] = a[i] + b[i];
    }
}

void kernal::vector_add(float *a, float *b, float *c, int n)
{
    int size = n * sizeof(float);
    float *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    kernal_vector_add<<<(n + 255) / 256, 256>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
// GPU function called from host code or device code
/*__global__ void mykernel(void) {

}

// Call to device code with kernel launch config
mykernel<<<1, 1>>>();

// Device pointers, just numbers
// Device pointers shouldn't be dereferenced in host code
// Host pointers shouldn't be dereferenced in device code
cudaMalloc(), cudaFree(), cudaMemcpy()

// Launch N copies of kernel to work on N instances
add<<<N, 1>>>(); // N is length of vector

blockIdx.xyz // Represents block/worker (parallel invocation of kernel) structure in multiple dimensions
*/
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdlib.h>
#include <iostream>

__global__ void add(int* a, int* b, int* c) {
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

#define N 512
int main(void) {
	int* a, * b, * c; // host copies of a, b, c
	int* d_a, * d_b, * d_c; // device copies of a, b, c
	int size = N * sizeof(int);
	// Alloc space for device copies of a, b, c
	cudaMalloc((void **)&d_a, size); // returns error code if something goes wrong
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);
	// Alloc space for host copies of a, b, c
	a = (int*)malloc(size);
	b = (int*)malloc(size);
	c = (int*)malloc(size);
	// Copy inputs to device
	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
	// Launch add() kernel on GPU with N blocks/workers
	add<<<N,1>>>(d_a, d_b, d_c);
	// Copy results back to host
	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

	// there could be template generic kernels :O
	for (int i = 0; i < N; i++) {
		std::cout << c[i];
	}
	std::cout << std::endl;

	free(a);
	free(b);
	free(c);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;

}
#include "_hello.cuh"

__global__ void hello() {

	printf("Hello from block: %u, thread: %u\n", blockIdx.x, threadIdx.x);
}

void helloWorld() {
	hello << <2, 2 >> > ();
	cudaDeviceSynchronize();
}


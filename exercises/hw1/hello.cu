#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void hello(){

  printf("Hello from block: %u, thread: %u\n", blockIdx.x, threadIdx.x);
}

void helloWorld() {
	hello<<<2, 2>>>();
	cudaDeviceSynchronize();
}


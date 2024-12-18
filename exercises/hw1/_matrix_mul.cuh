#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
// these are just for timing measurments
#include <time.h>

__global__ void mmul(const float* A, const float* B, float* C, int ds);

int matMul();
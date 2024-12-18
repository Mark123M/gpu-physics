#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void vadd(const float* A, const float* B, float* C, int ds);

int vecAdd();
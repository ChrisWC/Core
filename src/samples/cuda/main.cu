#include <stdio.h>
#include <assert.h>

#include <cuda_runtime.h>

//#include <helper_functions.h>
//#include <helper_cuda.h>

#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif
__global__ void testKernel(int val)
{
	printf("[%d, %d]:\t\tValue is:%d\n", blockIdx.y*gridDim.x+blockIdx.x, \
		threadIdx.z*blockDim.x*blockDim.y+threadIdx.y*blockDim.x+threadIdx.x, val);
}

int main(int argc, char **argv)
{
	int devID;
	cudaDeviceProp props;

//	devID = findCudaDevice(argc, (const char **) argv);

	//checkCudaErrors(cudaGetDevice(&devID));
	//checkCudaErrors(cudaGetDeviceProperties(&props, devID));

	//printf("Device %d: \"%s\" with Compute %d.%d capability\n", devID, props.name, props.major, props.minor);

	printf("printf() is called. Output:\n\n");

	dim3 dimGrid(2,2);
	dim3 dimBlock(2,2,2);

	testKernel<<<dimGrid, dimBlock>>>(10);
	cudaDeviceSynchronize();

	cudaDeviceReset();

	return EXIT_SUCCESS;
}

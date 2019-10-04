#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#define N 5

__global__ void add(int* a, int* b, int* c)
{
	int tid;
	tid = threadIdx.x;
	c[tid] = a[tid] + b[tid];
}


int main(void)
{
	int a[N],b[N],c[N];
	
	int size=sizeof(int);

	int i;
	for(i=0;i<N;i++)
	{
	a[i] = i;
	b[i] = 2*i;
	}
	int *d_a, *d_b, *d_c;

	cudaMalloc((void **)&d_a,N*size);
	cudaMalloc((void **)&d_b,N*size);
	cudaMalloc((void **)&d_c,N*size);

	cudaMemcpy(d_a,a,N*size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,N*size,cudaMemcpyHostToDevice);
	

	add<<<1,N>>>(d_a,d_b,d_c);

	cudaMemcpy(c,d_c,size*N,cudaMemcpyDeviceToHost);

	for(i=0;i<N;i++)
	printf("Sum is %d\n",c[i]);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;

}
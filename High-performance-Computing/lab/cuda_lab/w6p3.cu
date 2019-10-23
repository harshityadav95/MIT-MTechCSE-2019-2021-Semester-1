#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void swap(int *a, int n)
{

	int temp;

	int i = blockIdx.x  * blockDim.x + 0;
	int j = blockIdx.x  * blockDim.x + 1;

	temp = a[i];
	a[i]= a[j];
	a[j]=temp;

}

int main(void)
{
	int n,a[100],i;
	printf("Enter no of elements in the array\n");
	scanf("%d", &n);
	printf("Enter the array elements\n");
	for(i=0;i<n;i++)
	{
	scanf("%d", &a[i]);
	}

	int *d_a,size;

	size = sizeof(int);

	cudaMalloc((void **)&d_a,n*size);
	
	
	cudaMemcpy(d_a,a,n*size,cudaMemcpyHostToDevice);

	dim3 dimgrid(n/2,1,1);
	dim3 dimblock(2,1,1);

	swap<<<dimgrid,dimblock>>>(d_a,n);

	cudaMemcpy(a,d_a,n*size,cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
	{
	printf("%d\n", a[i]);
	}

	cudaFree(d_a);
	

	return 0;
}
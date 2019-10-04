#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdio.h>

__global__ void Add(int *a, int *b, int *c, int n)
{
	int id,i;
	id = threadIdx.x;
		c[id] = a[id]+b[id];
}

int main()
{
	int a[100],b[100],c[100],n,i;
	int size, *d_a, *d_b, *d_c;

	printf("\nEnter N\n");
	scanf("%d", &n);

	printf("\nEnter MATRIX A\n");
	for(i=0;i<n*n;i++)
	{
		scanf("%d", &a[i]);
	}
	

	printf("\nEnter MATRIX B\n");
	for(i=0;i<n*n;i++)
	{
		scanf("%d", &b[i]);
	}

	size = sizeof(int);

	cudaMalloc((void **)&d_a,n*n*size);
	cudaMalloc((void **)&d_b,n*n*size);
	cudaMalloc((void **)&d_c,n*n*size);

	cudaMemcpy(d_a,a,n*n*size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,n*n*size,cudaMemcpyHostToDevice);

	Add<<<1,n*n>>>(d_a,d_b,d_c,n);

	cudaMemcpy(c,d_c,size*n*n,cudaMemcpyDeviceToHost);

	printf("Addition of rows\n");
	for(i=0;i<n*n;i++)
	{
		printf("%d\t", c[i]);
	}

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;


}
#include<stdio.h>
#include"cuda_runtime.h"
#include"device_launch_parameters.h"
__global__ void add(int *a,int *b,int *c)
{
	int tid=threadIdx.x;
	c[tid]=a[tid]+b[tid];
}
int main()
{	

	int n,a[10],b[10],c[10];
	printf("\nValue of N:");
	scanf("%d",&n);
	printf("\n Enter the Values of array A:");
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&a[i]);
	}
	printf("\n Enter the Value of array B :");
	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&b[i]);
	}
	int *d_a,*d_b,*d_c;
	int size=sizeof(int);
	cudaMalloc((void**)&d_a,size*n);
	cudaMalloc((void**)&d_b,size*n);
	cudaMalloc((void**)&d_c,size*n);
	cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size*n,cudaMemcpyHostToDevice);
	add<<<1,n>>>(d_a,d_b,d_c);
	cudaMemcpy(c,d_c,size*n,cudaMemcpyDeviceToHost);
	printf("The Sum of the array is :");
	for (int i = 0; i < n; ++i)
	{
		printf("%d ",c[i]);
	}
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 1;




}	
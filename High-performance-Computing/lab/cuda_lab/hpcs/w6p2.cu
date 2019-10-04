
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void convert(int *a, int *b,int n)
{
int tid,octalnum=0,i=1,num;
tid = threadIdx.x;

num=a[tid];

while(num>0)
{
 octalnum+=(num%8)*i;
 num=num/8;
 i=i*10;
 }
 b[tid]=octalnum;
}

int main(void)
{
	
	int a[100],n,i,b[100],size;
	printf("Enter the no of decimal values to be converted to Octal\n");
	scanf("%d", &n);
	printf("Enter the Decimal values\n");
	for(i=0;i<n;i++)
	{
	scanf("%d", &a[i]);
	}

	int *d_a, *d_b;
	size = sizeof(int);

	cudaMalloc((void **)&d_a,n*size);
	cudaMalloc((void **)&d_b,n*size);

	cudaMemcpy(d_a,a,n*size,cudaMemcpyHostToDevice);

	convert<<<1,n>>>(d_a,d_b,n);

	cudaMemcpy(b,d_b,n*size,cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
	{
	printf("%d\n", b[i]);
	}

	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
	
}
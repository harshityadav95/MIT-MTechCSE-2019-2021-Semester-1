#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void add(int *a,int *b,int *c)
{
	int tid = threadIdx.x;
	c[tid] = a[tid] + b[tid];
}
int main(void)
{
	int i,a[10000],b[10000],c[10000],n;
	printf("Enter value of N:");
	scanf("%d",&n);
	printf("Enter array elements of array A\n");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);

	printf("Enter array elements of array B\n");
	for(i=0;i<n;i++)
		scanf("%d",&b[i]);	




int *d_a,*d_b,*d_c;
int size = sizeof(int);
cudaMalloc((void **)&d_a,size*n);
cudaMalloc((void **)&d_b,size*n);
cudaMalloc((void **)&d_c,size*n);

cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
cudaMemcpy(d_b,b,size*n,cudaMemcpyHostToDevice);
add<<<1,n>>>(d_a,d_b,d_c);
cudaMemcpy(c,d_c,size*n,cudaMemcpyDeviceToHost);
printf("Sum array is :");
for(i=0;i<n;i++)
	printf("%d\t",c[i]);

cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
return 0;
}
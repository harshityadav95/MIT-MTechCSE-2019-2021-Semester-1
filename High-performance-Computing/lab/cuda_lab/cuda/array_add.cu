#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void add(int *a,int *b,int*c){
	int tid = threadIdx.x;
	c[tid] = a[tid] + b[tid];
}

int main(void){
	int n,a[1000],b[1000],c[1000],i,size,*d_a,*d_b,*d_c;
	printf("Enter no. of elements:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		a[i] = i;
		b[i] = i*2;
	}
	size = sizeof(int);
	cudaMalloc((void **)&d_a,size*n);
	cudaMalloc((void **)&d_b,size*n);
	cudaMalloc((void **)&d_c,size*n);

	cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size*n,cudaMemcpyHostToDevice);

	add <<<1,n>>> (d_a,d_b,d_c);

	cudaMemcpy(c,d_c,size*n,cudaMemcpyDeviceToHost);
	for(i=0;i<n;i++)
		printf("%d\t",c[i]);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
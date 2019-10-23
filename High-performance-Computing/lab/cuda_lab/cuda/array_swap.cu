#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void add(int *a,int *b){
	int tid = threadIdx.x;
	if(tid %2 ==0){
		if(a[tid+1]!=NULL){
			b[tid+1] = a[tid];
			b[tid] = a[tid+1];
		}
	}
}

int main(void){
	int n,i,size,*d_a,*d_b;
	int a[1000],b[1000];
	printf("Enter no. of elements:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		a[i] = i;
	}
	size = sizeof(int);
	cudaMalloc((void **)&d_a,size*n);
	cudaMalloc((void **)&d_b,size*n);

	cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);

	add <<<1,n>>> (d_a,d_b);

	cudaMemcpy(b,d_b,size*n,cudaMemcpyDeviceToHost);
	for(i=0;i<n;i++)
		printf("%d\t",b[i]);
	printf("\n");
	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
}
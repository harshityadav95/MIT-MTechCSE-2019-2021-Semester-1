#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void matadd(int *a,int *b,int*c,int m,int n){
	int tid = threadIdx.x;
	//int sum,i,j;
	c[tid] = a[tid] + b[tid];
}

int main(void){
	int m,n,a[100],b[100],c[100],i,size,*d_a,*d_b,*d_c;
	printf("Enter M:\n");
	scanf("%d",&m);
	printf("Enter N:\n");
	scanf("%d",&n);
	printf("Enter matrix A:\n");
	for(i=0;i<m*n;i++){
		scanf("%d",&a[i]);
	}
	printf("Enter matrix B:\n");
	for(i=0;i<m*n;i++){
		scanf("%d",&b[i]);
	}
	size = sizeof(int);
	cudaMalloc((void **)&d_a,size*n*m);
	cudaMalloc((void **)&d_b,size*n*m);
	cudaMalloc((void **)&d_c,size*n*m);

	cudaMemcpy(d_a,a,size*n*m,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size*n*m,cudaMemcpyHostToDevice);
	cudaMemcpy(d_c,c,size*n*m,cudaMemcpyHostToDevice);

	matadd <<<1,m*n>>> (d_a,d_b,d_c,m,n);

	cudaMemcpy(c,d_c,size*n*m,cudaMemcpyDeviceToHost);
	for(i=0;i<m*n;i++){
		printf("%d\t",c[i]);
	}
	printf("\n");
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
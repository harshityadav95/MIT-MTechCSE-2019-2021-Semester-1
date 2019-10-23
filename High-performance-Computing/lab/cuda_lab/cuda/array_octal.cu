#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <math.h>

__global__ void add(int *a,int *b){
	int tid = threadIdx.x;
	int y=0,z,i=1;
	z = a[tid];
	while(z!=0){
		y += (z % 8)*i;
		i = i*10;
		z = z/8;
	}
	b[tid] = y;
}

int main(void){
	int n,a[1000],b[1000],i,size,*d_a,*d_b;
	printf("Enter no. of elements:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		//scanf("%d",&a[i]);
		a[i] = rand()/100000;
		printf("%d\t",a[i]);
	}
	printf("\n");
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
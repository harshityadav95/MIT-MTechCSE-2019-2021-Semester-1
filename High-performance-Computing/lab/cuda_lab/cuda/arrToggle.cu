#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <string.h>
__global__ void toggle(char *a){
	int tid = threadIdx.x;
	if (a[tid] >= 'A' && a[tid] <= 'Z')
		{a[tid]+=32;}
	else if(a[tid] >= 'a' && a[tid] <= 'z')
		{a[tid] -=32;}
}
int main(void){
	int n,size;
	char a[100],*d_a;
	printf("Enter the string to be toggled:\n");
	scanf("%s",a);
	n=strlen(a);
	size = sizeof(char);
	cudaMalloc((void **)&d_a,size*n);
	cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
	toggle <<<1,n>>> (d_a);
	cudaMemcpy(a,d_a,size*n,cudaMemcpyDeviceToHost);
		printf("%s",a);
	printf("\n");
	cudaFree(d_a);
	return 0;
}

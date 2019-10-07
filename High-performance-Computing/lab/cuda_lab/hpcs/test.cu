#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void star(char *a, int *n)
{   int i, j, t;
    int k = *n;
	int tid=threadIdx.x;
	j = k - tid - 1;
	t = (tid + 1) * 2 - 1;
	for(i = 0; i < t; i++){
	 a[tid * (k * 2 - 1) + j + i] = '*';
	}
}

int main(void)
{
	int i, N, j;
	scanf("%d", &N);
	
	int l = 2 * N - 1;
	char a[l][l];
	char *d_a;
	 int *d_b;
	int size=sizeof(char);
	int s = sizeof(int);
	cudaMalloc((void **)&d_a,size*l*l);
	cudaMalloc((void **)&d_b,s);
	cudaMemcpy(d_a,&a,size*l*l,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,&N,s,cudaMemcpyHostToDevice);
	star<<<1,N>>>(d_a,d_b);
	cudaMemcpy(a,d_a,size*l*l,cudaMemcpyDeviceToHost);
	for(i=0;i<l;i++)
	{
	for(j = 0; j < l; j++){
	if(a[i][j] == '*'){
	printf("%c", a[i][j]);
	}else{
	printf(" ");
	}
	}
	printf("\n");
	}
	return 0;
	}

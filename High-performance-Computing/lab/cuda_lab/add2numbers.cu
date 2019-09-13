#include<stdio.h>
#include"cuda_runtime.h"
#include"device_launch_parameters.h"
__global__ void add(int *a,int *b,int *c)
{
	*c=*a+*b;
}
int main()
{	
	int a,b,c;
	printf("\nValue of A:");
	scanf("%d",&a);
	printf("\nValue of b:");
	scanf("%d",&b);

	int *d_a,*d_b,*d_c;
	int size=sizeof(int);
	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	cudaMalloc((void**)&d_c,size);
	cudaMemcpy(d_a,&a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,&b,size,cudaMemcpyHostToDevice);
	add<<<1,1>>>(d_a,d_b,d_c);
	cudaMemcpy(&c,d_c,size,cudaMemcpyDeviceToHost);
	printf("The Sum of the Numbers is %d:",c);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 1;




}	
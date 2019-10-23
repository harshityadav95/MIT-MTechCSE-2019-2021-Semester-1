#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <string.h>
__global__ void ascii(char *a, int *b){
	int tid = threadIdx.x;
	b[tid] = int(a[tid]);
	printf("%d\t", b[tid]);
	printf("\n");
}
__global__ void reverse(int *b, int *c){
	int tid = threadIdx.x;
	c[tid]=0;
	while(b[tid] != 0)
    {
        c[tid] = c[tid]*10 + b[tid]%10;
        b[tid] /= 10;
    }
    printf("%d\t", c[tid]);
    printf("\n");
}
int main(void){
	int n, i, size, size1, b[100], *d_b, *d_c, c[100];
	char a[100], *d_a;
	printf("Enter the string to be toggled:\n");
	scanf("%s",a);
	n=strlen(a);
	//for(i=0; i<n; i++)
	//{
	//	b[i] = int(a[i]);
	//}
	size = sizeof(char);
	size1 = sizeof(int);
	cudaMalloc((void **)&d_a,size*n);
	cudaMalloc((void **)&d_b,size1*n);
	cudaMalloc((void **)&d_c,size1*n);
	cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
	ascii <<<1,n>>> (d_a, d_b);
	cudaMemcpy(b,d_b,size1*n,cudaMemcpyDeviceToHost);
	for(i=0; i<n; i++)	
		{printf("%d\t",b[i]);}
	printf("\n");
	cudaMemcpy(d_b,b,size1*n,cudaMemcpyHostToDevice);
	reverse <<<1,n>>> (d_b, d_c);
	cudaMemcpy(c,d_c,size1*n,cudaMemcpyDeviceToHost);
	for(i=0; i<n; i++)
		{
			if(c[i]>26 && c[i]<126)
				{printf("%c\t",c[i]);}
			else
				{printf("%d\t",c[i]);}
		}
	printf("\n");
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
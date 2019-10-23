#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdio.h>
#include<string.h>


__global__ void Toggle(char *a, char *b, int n)
{
	int tid;
	tid = threadIdx.x;
	if(a[tid]>='A' && a[tid]<='Z')
	{
	b[tid]=a[tid]+32;
	}
	else
	{
	b[tid]=a[tid]-32;
	}
}

int main()
{
	char a[100],b[100];

	int i,n,size;
	char *d_a, *d_b;

	printf("\nEnter the string\n");
	scanf("%s",a);

	n = strlen(a);
	printf("\nNo of charcaters is\t%d", n);

	
	size = sizeof(char);
	printf("\nSize is \t%d\n", size);

	cudaMalloc((void **)&d_a,n*size);
	cudaMalloc((void **)&d_b,n*size);
	

	cudaMemcpy(d_a,a,n*size,cudaMemcpyHostToDevice);
	

	Toggle<<<1,n>>>(d_a,d_b,n);

	cudaMemcpy(b,d_b,n*size,cudaMemcpyDeviceToHost);

	
		printf("\nToggled string is \n");
		for(i=0;i<n;i++)
		printf("%c",b[i]);
	
	cudaFree(d_a);
	cudaFree(d_b);
	
	return 0;


}
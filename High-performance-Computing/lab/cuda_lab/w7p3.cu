#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdio.h>
#include<string.h>


__global__ void copy(char *a, char *b, int n,int m)
{
	int tid;
	tid = threadIdx.x;
	int i=0;
	while(i<m)
	{
	b[i*n+tid]=a[tid];
	i++;
	}
	
}

int main()
{
	char a[100],b[100];

	int i,n,m,size;
	char *d_a, *d_b;

	printf("\nEnter the string\n");
	scanf("%s", a);

	printf("How many times you want to repeat the string?\n");
	scanf("%d", &m);

	n = strlen(a);
	printf("\nNo of characters is %d\t", n);

	
	size = sizeof(char);
	printf("\nSize is \t%d\n", size);

	cudaMalloc((void **)&d_a,n*size);
	cudaMalloc((void **)&d_b,n*m*size);
	

	cudaMemcpy(d_a,a,n*size,cudaMemcpyHostToDevice);
	

	copy<<<1,n>>>(d_a,d_b,n,m);

	cudaMemcpy(b,d_b,n*m*size,cudaMemcpyDeviceToHost);

		printf("\nRepeated string is \n");
		for(i=0;i<n*m;i++)
		printf("%c",b[i]);
	
	cudaFree(d_a);
	cudaFree(d_b);
	
	return 0;


}
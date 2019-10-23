#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void sort(char *s, int n, char *b)
{
	int id,i,c=0;
	id = threadIdx.x;
	for(i=0;i<n;i++)
	{
		if(id==i)
		continue;
		else if(s[i]<s[id])
		{
		c++;
		}
		b[c]=s[id];
	}
	
}

int main(void)
{
	char s[100],b[100];
	int n,i;
	printf("Enter the string\n");
	scanf("%s", s);

	n = strlen(s);
	char *d_s, *d_b;
	int size;

	size = sizeof(char);

	cudaMalloc((void**)&d_s, n*size);
	cudaMalloc((void**)&d_b, n*size);

	cudaMemcpy(d_s,s,n*size, cudaMemcpyHostToDevice);

	sort<<<1,n>>>(d_s,n,d_b);

	cudaMemcpy(b,d_b,n*size, cudaMemcpyDeviceToHost);

	for(i=0;i<n;i++)
	printf("%c",b[i]);

	cudaFree(d_s);
	cudaFree(d_b);

	return 0;
}
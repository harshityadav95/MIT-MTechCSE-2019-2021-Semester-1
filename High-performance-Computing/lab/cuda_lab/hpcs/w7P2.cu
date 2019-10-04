#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void convert(char *s, int n)
{
	int id,r=0,k=0;
	id = threadIdx.x;
	int z;
	z=s[id];
	while(z>0)
		{
			r = z%10;
			z=z/10;
			k = k*10+r;
		}
	s[id]=(char)k;


}

int main(void)
{
	int n,i;
	char s[100];
	
	printf("Enter the string.\n");
	scanf("%s\n",s);

	n = strlen(s);
	//printf("%d",n);

	int size;
	size = sizeof(char);
	char *d_s;

	cudaMalloc((void**)&d_s,n*size);	
	cudaMemcpy(d_s,s,n*size,cudaMemcpyHostToDevice);

	convert<<<1,n>>>(d_s,n);

	cudaMemcpy(s,d_s,n*size,cudaMemcpyDeviceToHost);
	
	printf("\n");
	for(i=0;i<n;i++)
	printf("%c",s[i]);

	cudaFree(d_s);
	return 0;
}
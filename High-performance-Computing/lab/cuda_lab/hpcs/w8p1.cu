#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void matrixmul(int *a,int *b,int *c,int m,int n,int p)
{
int id = threadIdx.x;
int sum,i,j;
for(i=0;i<m;i++)
{
	sum=0;
	for(j=0;j<p;j++)
	{
	sum+=(a[i*n+j]*b[j*p+id]);
	}
	c[i*p+id]=sum;

}
}

int main(void)
{
	clock_t t;
	t = clock();
	int m,n,a[100], b[100], c[100],p,i,j;
	int size,*d_a,*d_b,*d_c;

	size = sizeof(int);
	printf("Enter value of m, n, p\n");
	scanf("%d%d%d",&m,&n,&p);


	printf("Enter Matrix A\n");
	for(i=0;i<m*n;i++)
	{
	scanf("%d",&a[i]);
	}


	printf("Enter Matrix B\n");
	for(i=0;i<n*p;i++)
	{
	scanf("%d",&b[i]);
	}

	cudaMalloc((void **)&d_a,m*n*size);
	cudaMalloc((void **)&d_b,p*n*size);
	cudaMalloc((void **)&d_c,m*p*size);

	cudaMemcpy(d_a,a,m*n*size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,n*p*size,cudaMemcpyHostToDevice);

	cudaEvent_t start, stop;
	float elapsed_time_ms;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	
	cudaEventRecord(start,0);
	
	matrixmul<<<1,p>>>(d_a,d_b,d_c,m,n,p);

	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsed_time_ms,start,stop);
	printf("\nTime to calculate results inside GPU is: %fms\n",elapsed_time_ms);


	cudaMemcpy(c,d_c,size*m*p,cudaMemcpyDeviceToHost);

	printf("\nMultiplication is :\n");
	for(i=0;i<m;i++)
	{
	printf("\n");
	for(j=0;j<p;j++)
	{
	printf("%d\t",c[i*m+j]);
	}
	}
	
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	t = clock()-t;
	double time_taken;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("\nEntire program took %f seconds to execute\n", time_taken);


	return 0;

}

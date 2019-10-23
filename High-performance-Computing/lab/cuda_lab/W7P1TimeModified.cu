
#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdio.h>
#include<string.h>
#include<time.h>


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
	clock_t t;
	t = clock();
	char a[100],b[100];
	int i,n,size;
	char *d_a, *d_b;
	

	printf("\nEnter the string\n");
	scanf("%s", a);

	n = strlen(a);
	printf("\nNo of charcaters is\t%d", n);

	
	size = sizeof(char);
	printf("\nSize is \t%d\n", size);

	cudaMalloc((void **)&d_a,n*size);
	cudaMalloc((void **)&d_b,n*size);
	

	cudaMemcpy(d_a,a,n*size,cudaMemcpyHostToDevice);

	cudaEvent_t start, stop;
	float elapsed_time_ms;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	
	cudaEventRecord(start,0);

	Toggle<<<1,n>>>(d_a,d_b,n);

	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsed_time_ms,start,stop);
	printf("\nTime to calculate results inside GPU is: %fms\n",elapsed_time_ms);


	cudaMemcpy(b,d_b,n*size,cudaMemcpyDeviceToHost);

	
		printf("\nToggled string is \n");
		for(i=0;i<n;i++)
		printf("%c",b[i]);
	
	cudaFree(d_a);
	cudaFree(d_b);
	t = clock()-t;
	double time_taken;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("\nEntire program took %f seconds to execute\n", time_taken);

	return 0;


}
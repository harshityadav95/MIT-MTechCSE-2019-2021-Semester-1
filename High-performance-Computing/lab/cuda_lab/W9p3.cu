#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void Even(int* a,int n)
{
	int k;
	int tid = threadIdx.x;
	if(tid%2 == 0 && tid != n-1)
	{
		//printf("etid = %d\n",tid);
		if(a[tid] > a[tid+1]){//printf("even : %d\n",a[tid]);
		k = a[tid];
		a[tid] = a[tid+1];
		a[tid+1] = k;
		}
	}
}
__global__ void Odd(int* a,int n)
{
	int k;
	int tid = threadIdx.x;
	if(tid%2 != 0 && tid != n-1)
	{
	//printf("otid = %d\n",tid);
	if(a[tid] > a[tid+1]){
		//printf("odd : %d\n",a[tid]);
		k = a[tid];
		a[tid] = a[tid+1];
		a[tid+1] =  k;
	}
	}
}
int main(void)
{
	int N = 0, i, sz;
	int* d_a;

	printf("Enter Array size:\n");
	scanf("%d", &N);

	int A[100];
	printf("Enter string:\n");

	for (i = 0; i < N; i++)
	{
		A[i] = N-i;
		//scanf("%d", &A[i]);
		printf("%d ",A[i]);
	}
	printf("\n");

	sz = sizeof(int) * N;
	cudaMalloc((void**)&d_a, sz);

	cudaMemcpy(d_a, A, sz, cudaMemcpyHostToDevice);
	int val = N/2;
	if(N%2 != 0)
	{
		val = val + 1;
	}

	for(i=0;i<val;i++)
	{
		Odd<<<1, N>>>(d_a,N);
		Even<<<1, N>>>(d_a,N);
	}
	cudaMemcpy(A, d_a, sz, cudaMemcpyDeviceToHost);
	for (i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
	cudaFree(d_a);
}
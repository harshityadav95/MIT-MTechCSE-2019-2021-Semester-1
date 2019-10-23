#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void RevWrd(char* a,char* c,int n,int* pos)
{
	int i,k;
	int tid = threadIdx.x;
	int strIn = pos[tid];
	int nstrIn = pos[tid + 1];
	if (nstrIn == 0)
	{
		nstrIn = n;
	}
	k = nstrIn - 2;
	printf("i=%d ,j=%d", strIn, nstrIn);
	for (i = strIn; i < nstrIn;i++)
	{
		c[k--] = a[i];
	}
}
void MyWords(char* arr, int* n,int len)
{
	int i=0,k=0;
	n[k++] = 0;
	while (i != len)
	{
		if (arr[i++] == ' ')
		{
			n[k++] = i;
		}
	}
	n[k] = len;
}
int main(void)
{
	int N = 0, i, sz, strLth;
	char A[100],C[100]; int pos[20];
	char* d_a;char* d_c; int* d_pos;

	printf("Enter no of words in string:\n");
	scanf("%d", &N);
	printf("Enter string:\n");
	scanf(" %[^\n]s", A);
	strLth = strlen(A);
	printf("Strlen %d", strLth);
	MyWords(A, pos,strLth);
	//pos[N + 1] = strLth;
	for (i = 0;i < N+1 ; i++)
	{
		printf(" pos %d =%d\t", i, pos[i]);
	}
	sz = sizeof(char) * strLth;
	cudaMalloc((void**)&d_a, sz);
	cudaMalloc((void**)&d_pos, N * sizeof(int));
	cudaMalloc((void**)&d_c, sz);

	cudaMemcpy(d_a, A, sz, cudaMemcpyHostToDevice);
	cudaMemcpy(d_pos, pos, N * sizeof(int), cudaMemcpyHostToDevice);
	
	RevWrd << <1, N >> > (d_a,d_c,strLth,d_pos);

	cudaMemcpy(C, d_c, sz, cudaMemcpyDeviceToHost);
	printf("%s", C);

	cudaFree(d_a);
	cudaFree(d_pos);
	cudaFree(d_c);
}
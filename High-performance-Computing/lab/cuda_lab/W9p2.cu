#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void S_Sort(char* a,char* b,int n,int* pos)
{
	int i=0,k=0,strIn=0;
	int tid = threadIdx.x;
	if(a[tid] == ' ')
	{
		b[tid] = ' ';
	}
	else{
	for (i = 0; i < tid; i++)
	{
		if (a[i] == ' ')
		{
			k++;
			//printf("%d str %d\n",tid,strIn);
		}
	}
	char min;
	min = a[tid];
	strIn = pos[k];
	int nstrIn = pos[k + 1];
	if (nstrIn == 0)
	{
		nstrIn = n+1;
	}
	int inc=0;
	for (i = strIn; i < nstrIn-1;i++)
	{
		if (a[i] < min)
		{
			inc++;printf("min %c tid %d\n",min,tid);
		}
	}
	printf("b= %d ; a[tid]=%d\n",inc+strIn,tid);
	b[inc+strIn] = a[tid];
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
	int pos[20];
	char* d_a;char* d_c; int* d_pos;

	printf("Enter no of words in string:\n");
	scanf("%d", &N);
	char A[50],C[50];
	printf("Enter string:\n");
	scanf(" %[^\n]s", A);
	strLth = strlen(A);
	printf("Strlen %d", strLth);
	MyWords(A, pos,strLth);
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
	

	S_Sort << <1,strLth >> > (d_a,d_c,strLth,d_pos);

	cudaMemcpy(C, d_c, sz, cudaMemcpyDeviceToHost);
	for(i=0;i<strLth;i++)
	{
		printf("%c", C[i]);
	}
	

	cudaFree(d_a);
	cudaFree(d_pos);
	cudaFree(d_c);
}
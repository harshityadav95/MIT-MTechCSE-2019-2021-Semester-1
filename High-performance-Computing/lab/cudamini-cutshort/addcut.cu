#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<time.h>
#define arm 32
__device__ int globalArray[32];
__global__ void add(int *a,int *c)
{
	
    int tid = threadIdx.x;
    int temp=a[tid];
    int count=0;
    while(temp!=0)
    {
        count++;
        temp=temp/2;
    }
    atomicAdd(&globalArray[count], 1);
    c[count]=globalArray[count];

}
int main(void)
{
    int arr[20];
    int count=20;
    int bitband[arm]={0};
    for (int i = 0; i < 20; ++i)
    {
        arr[i]=i;
    }

int *d_a,*d_c;
int size = sizeof(int);
cudaMalloc((void **)&d_a,size*count);

cudaMalloc((void **)&d_c,size*arm);

cudaMemcpy(d_a,arr,size*count,cudaMemcpyHostToDevice);


add<<<1,count>>>(d_a,d_c);
cudaMemcpy(bitband,d_c,size*arm,cudaMemcpyDeviceToHost);
   for (int i = 0; i < 20; ++i)
   {
       printf("%d\n",bitband[i]);
   }

cudaFree(d_a);
cudaFree(d_c);
return 0;
}
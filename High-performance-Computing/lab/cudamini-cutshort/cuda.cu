#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
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
int bitcount(int num);
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
void quicksort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quicksort(arr, low, pi - 1); 
        quicksort(arr, pi + 1, high); 
    } 
} 

int main(void)
{
	int i,arr[50000]={0},bitband[arm]={0},n;
	int pos;
	 int resultant[50000]={0};
	 int bitmap[arm]={0};
	int num;
	int count=0;
       ///a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        /*for ( i = 0; i < count; ++i)
        {
            a[i]=i+1;
        }*/
    	FILE *fptr;
    	fptr = fopen("integers", "r");
		printf("\ncounting the File:\n");
		while ( (num = getw(fptr)) != EOF ) 
		{
    		arr[count]=num;
    		count++;

  		}
  		fclose(fptr);
  		n=count;


int *d_a,*d_b,*d_c;
int size = sizeof(int);
cudaMalloc((void **)&d_a,size*n);

cudaMalloc((void **)&d_c,size*arm);

cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
clock_t start,stop;
start=clock();
add<<<1,n>>>(d_a,d_c);
cudaMemcpy(bitband,d_c,size*arm,cudaMemcpyDeviceToHost);
   for(int i=1;i<=arm;i++)
        {
            bitband[i] += bitband[i-1];
        }
          for(int i=0;i<count;i++)
        {
            pos=bitcount(arr[i]);
            resultant[ ((pos==0)?0:bitband[pos-1]) + bitmap[pos] ] = arr[i];
            bitmap[pos] += 1;
        }

for(int i=0;i<count;i++)
        {
            pos=bitcount(arr[i]);
            resultant[ ((pos==0)?0:bitband[pos-1]) + bitmap[pos] ] = arr[i];
            bitmap[pos] += 1;
        }

        for(int i=1;i<=arm;i++)
        {
            quicksort(resultant,bitband[i-1],bitband[i]-1);
        }
        stop=clock();
     
        printf("CLOCKS PER SECOND = %ld\n",CLOCKS_PER_SEC);
        printf("START CLOCK = %ld \nSTOP CLOCK = %ld \n",start,stop);
        printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);


cudaFree(d_a);
cudaFree(d_c);
return 0;
}
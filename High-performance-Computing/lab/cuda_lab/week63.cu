#include <stdio.h>
#include <stdlib.h>

__global__ void add(int *a,int *b)
{
  int tid = threadIdx.x;
  int n=a[tid];
  if(tid+2<*b && tid<(*b)/2)
    {
        a[tid]=a[tid+2];
        a[tid+2]=n;
    }
 
    
}
int main(void)
{
  int n,a[20],c[20];
  printf("Enter value of N:");
  n=5;
  printf("Enter array elements of array A\n");
  for(int i=0;i<n;i++)
  {
      a[i]=i;
  }
  
int *d_a,*d_b,*d;
int size = sizeof(int);
cudaMalloc((void **)&d_a,size*n);
cudaMalloc((void **)&d_b,size);
    
cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
cudaMemcpy(d_b,&n,size,cudaMemcpyHostToDevice);
add<<<1,n>>>(d_a,d_b);
cudaMemcpy(c,d_a,size*n,cudaMemcpyDeviceToHost);
printf("array is :");
for(int i=0;i<n;i++)
{
           printf("%d ",c[i]);
}

    

cudaFree(d_a);
cudaFree(d_b);
return 0;
}
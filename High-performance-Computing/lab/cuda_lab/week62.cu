#include <stdio.h>
#include <stdlib.h>

__global__ void add(int *a,int *c)
{
	int tid = threadIdx.x;
    int n= a[tid] ;

  
    int temp=0,temp1=0;
    while(n!=0)
    {
        int t=n%8;
        temp=temp*10+t;
        n=n/8;
    }
    while(temp!=0)
    {
        int t=temp%10;
        temp1=temp1*10+t;
        temp=temp/10;
    }
    c[tid]=temp1;
    
    
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
	
int *d_a,*d_c;
int size = sizeof(int);
cudaMalloc((void **)&d_a,size*n);
cudaMalloc((void **)&d_c,size*n);
cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
add<<<1,n>>>(d_a,d_c);
cudaMemcpy(c,d_c,size*n,cudaMemcpyDeviceToHost);
printf("Octal array is :");
for(int i=0;i<n;i++)
{
           printf("%d ",c[i]);
}

    

cudaFree(d_a);
cudaFree(d_c);
return 0;
}
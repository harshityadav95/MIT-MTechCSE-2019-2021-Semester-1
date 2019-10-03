
__global__ void add(int *a,int *b,int *c)
{
	int tid = threadIdx.x;
	c[tid] = a[tid] + b[tid];
}
int main(void)
{
	int a[100],b[100],c[100],n;
	printf("Enter value of N:");
  n=3;
	printf("Enter array elements of array A\n");
  for(int i=0;i<n;i++)
  {
      a[i]=i;
  }
	printf("Enter array elements of array B\n");
	 for(int i=0;i<n;i++)
  {
      b[i]=i;
  }



int *d_a,*d_b,*d_c;
int size = sizeof(int);
cudaMalloc((void **)&d_a,size*n);
cudaMalloc((void **)&d_b,size*n);
cudaMalloc((void **)&d_c,size*n);

cudaMemcpy(d_a,a,size*n,cudaMemcpyHostToDevice);
cudaMemcpy(d_b,b,size*n,cudaMemcpyHostToDevice);
add<<<1,n>>>(d_a,d_b,d_c);
cudaMemcpy(c,d_c,size*n,cudaMemcpyDeviceToHost);
printf("Sum array is :");



    	 for(int i=0;i<n;i++)
  {
           printf("%d ",c[i]);
  }

    

cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
return 0;
}
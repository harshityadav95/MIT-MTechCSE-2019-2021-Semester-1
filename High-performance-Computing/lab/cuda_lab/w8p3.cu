#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdio.h>

__global__ void convert(int *b, int *c, int n)
{
	int tx,ty,i;
	
	tx = threadIdx.x;
	ty = threadIdx.y;

	
	if(tx==ty)
	{
	c[tx*n+ty]=0;
	}
	
	else if(tx>ty)
	{
	int fact = 1;
	for(i=1;i<b[ty*n+tx];i++)
	{
	fact += fact * i;
	}
	c[ty*n+tx]=fact;
	//printf("\nx = %d, y= %d ,fact =%d",tx,ty,fact);
	}

	else if(ty>tx)
	{
	int num=b[ty*n+tx];
	int r=0; 
	while(num>0)
	{
	r+=num%10;
	num=num/10;
	}
	c[ty*n+tx]=r;
	//printf("\nx = %d, y= %d ,num =%d",tx,ty,r);
	}


}


int main(void)
{
	int n,i,j,a[3][3],b[9],c[9];
	int  *d_b,*d_c, size;

	printf("Enter value of n\n");
	scanf("%d", &n);

	printf("Enter the elements of the matrix\n");
	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
	scanf("%d", &a[i][j]);
	}
	}

	/*for(i=0;i<n*n;i++)
	{
	b[i]=a[i][j];
	}*/

	size = sizeof(int);

	cudaMalloc((void **)&d_b,n*n*size);
	cudaMalloc((void **)&d_c,n*n*size);
	
	cudaMemcpy(d_b,a,n*n*size,cudaMemcpyHostToDevice);

	dim3 dimgrid(1,1,1);
	dim3 dimblock(n,n,1);
	
	convert<<<dimgrid,dimblock>>>(d_b,d_c,n);

	cudaMemcpy(c,d_c,n*n*size,cudaMemcpyDeviceToHost);
	printf("\n");
	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
		printf("%d\t", c[i*n+j]);
	}
	printf("\n");
	}
		
	
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;

}
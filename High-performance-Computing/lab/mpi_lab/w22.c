

#include<stdio.h>
#include<mpi.h>
#include<string.h>

void main(int argc,char *argv[])
{
int rank,size,n,i,A[20],B[20],x,c=0,d=0;
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

if(rank == 0)
{
	printf("Enter the number of elements of array\n");
	scanf("%d",&n);
	printf("Enter the elements of array\n");
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
	printf("Enter the element to be found in array\n");
	scanf("%d",&x);
	printf("\nThe array is:\n");
	for(i=0;i<n;i++)
		printf(" %d ",A[i]);
	MPI_Send(&x,1,MPI_INT,1,3,MPI_COMM_WORLD);
	MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
	MPI_Send(&A[n/2],n/2,MPI_INT,1,1,MPI_COMM_WORLD);
	for(i=0;i<n/2;i++)
	{
		if(A[i]==x)
		{
			printf("\nThe element is present in array at index %d\n",i+1);
			c++;
		}
	}
	MPI_Recv(&d,1,MPI_INT,1,2,MPI_COMM_WORLD,&status);
	c=c+d;
	printf("\nThe element is found %d times\n",c);

}
else if(rank==1)
{
	MPI_Recv(&x,1,MPI_INT,0,3,MPI_COMM_WORLD,&status);
	MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
	MPI_Recv(&B[0],n/2,MPI_INT,0,1,MPI_COMM_WORLD,&status);
	for(i=0;i<n/2;i++)
	{
			if(B[i]==x)
			{
				printf("\nThe element is present in array at index %d\n",i+1+n/2);
				d++;
			}
		}

	MPI_Send(&d,1,MPI_INT,0,2,MPI_COMM_WORLD);
}
MPI_Finalize();
}

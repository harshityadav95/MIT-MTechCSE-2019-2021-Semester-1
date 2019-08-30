#include<stdio.h>
#include<mpi.h>
#include<string.h>
int fact(int n)
{
	 if(n==0)
	return 1;
	else return n*fact(n-1);

}
void main(int argc,char *argv[])
{
int rank,size,i,n,b,A[20];
MPI_Status status;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

if(rank == 0)
{
	printf("Enter the %d elements of array\n",size);
	for(i=0;i<size;i++)
		scanf("%d",&A[i]);
	printf("\nThe elements are:\n");
	for(i=0;i<size;i++)
		printf(" %d ",A[i]);
}
MPI_Scatter(&A[0],1,MPI_INT,&b,1,MPI_INT,0,MPI_COMM_WORLD);

printf("Process of rank %d has factorial value %d for number %d\n",rank,fact(b),b);

MPI_Finalize();
}
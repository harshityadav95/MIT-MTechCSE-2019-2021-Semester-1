#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<math.h>

void main(int argc,char *argv[])
{
int rank,size,i,m,sum=0,A[20],b[10],c[10];
MPI_Status status;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

if(rank == 0)
{
	printf("Enter the number of elements required for each of the %d arrays\n",size);
	printf("Enter value for m\n");
	scanf("%d",&m);
	for(i=0;i<size*m;i++)
		
		scanf("%d",&A[i]);
}
MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Scatter(&A[0],m,MPI_INT,&b[0],m,MPI_INT,0,MPI_COMM_WORLD);

for(i=0;i<m;i++)
	{
		c[i]=pow(b[i],rank+2);
	}

for(i=0;i<m;i++)
{

	printf("For rank %d the value for element %d is %d\n",rank,b[i],c[i]);
}
MPI_Finalize();
}
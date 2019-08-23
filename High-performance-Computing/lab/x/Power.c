#include<stdio.h>
#include<mpi.h>
#include<math.h>
#include<unistd.h>

void main(int argc,char* argv[])
{

int myrank,size,i,m,a[100],b[100],c[100],counter;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
if(myrank==0)
{
	printf("Enter the value of M\n");
	scanf("%d",&m);
	printf("Enter the n*m elements\n");
	for(i=0;i<size*m;i++)
		scanf("%d",&a[i]);
}
MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Scatter(&a,m,MPI_INT,&b,m,MPI_INT,0,MPI_COMM_WORLD);
counter=myrank;
counter=counter+2;

	for(i=0;i<m;i++)
	{
		b[i]=pow(b[i],counter);
	}

MPI_Gather(&b,m,MPI_INT,&c,m,MPI_INT,0,MPI_COMM_WORLD);
if(myrank==0)
{
	printf("The gathered elements are");
	for(i=0;i<size*m;i++)
		printf("%d\t",c[i]);
	printf("\n");
}

MPI_Finalize();
}

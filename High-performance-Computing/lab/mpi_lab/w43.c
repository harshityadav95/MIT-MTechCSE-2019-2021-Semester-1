#include<stdio.h>
#include<mpi.h>

void main(int argc,char* argv[])
{

int myrank,size,i,a[50],j,b[100],c[100],d[50],count=0,key,fcount=0;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
if(myrank==0)
{
	printf("Enter the 4X4 matrix\n");
	for(i=0;i<4*4;i++)
		scanf("%d",&a[i]);

}
MPI_Scatter(&a,4,MPI_INT,&c,4,MPI_INT,0,MPI_COMM_WORLD);
MPI_Scan(&c,&b,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
MPI_Gather(&b,4,MPI_INT,&d,4,MPI_INT,0,MPI_COMM_WORLD);
if(myrank==0)
{
	printf("Output marix");
	for(int j=0;j<4;j++)
	{
		printf("\n");
		for(i=0;i<4;i++)
			printf("%d\t",d[i+(j*4)]);
	}
}
MPI_Finalize();
}

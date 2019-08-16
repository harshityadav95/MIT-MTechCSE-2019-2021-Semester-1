#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int size,rank;
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int n,a[100];
	if(rank==0)
	{
		printf("%d the size of the process is ",size);
		printf("\n Enter the Value of N :");
		scanf("%d",&n);
		printf("\n Enter the Elements of the Array :\n");
		for (int i = 0; i < size*n;++i)
		{
			scanf("%d",&a[i]);
			
		}
		printf("\n Prining the Elements of the Array :\n");
		for (int i = 0; i < size*n;++i)
		{
			printf("%d",a[i]);
			
		}
	}
	MPI_Finalize();



}
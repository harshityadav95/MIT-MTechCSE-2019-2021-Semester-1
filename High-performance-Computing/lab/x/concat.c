#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size;
	int n,i,j;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	char s1[100],s2[100],a[100],b[100];
	
	if(rank == 0)
	{
		printf("Enter the first string\n");
		scanf("%s",s1);
		printf("Enter the second string\n");
		scanf("%s",s2);
		n = strlen(s1);
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&s1[0],1,MPI_BYTE,&a[0],1,MPI_BYTE,0,MPI_COMM_WORLD);

	MPI_Scatter(&s2[0],1,MPI_BYTE,&a[1],1,MPI_BYTE,0,MPI_COMM_WORLD);

	MPI_Gather(&a[0],2,MPI_BYTE,&b[0],2,MPI_BYTE,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
		printf("%s",b);
	}
	MPI_Finalize();
	return 0;
}

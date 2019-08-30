#include <stdio.h>
#include <mpi.h>

void main(int argc,char *argv[])
{
	int rank,size,i,a[20],j,b[20],c=0;
	int key,c1=0;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		printf("Enter 3*3 matrix\n");
		for(i=0;i<3*3;i++)
		{
			scanf("%d",&a[i]);
		}
		printf("Enter the element to be searched\n");
		scanf("%d",&key);
	}

	MPI_Bcast(&key,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&a,3,MPI_INT,&b,3,MPI_INT,0,MPI_COMM_WORLD);

	for(i=0;i<3;i++)
	{
		if(key == b[i])
		{
			c++;
		}
	}
	
	MPI_Reduce(&c,&c1,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
 		printf("Element %d occured %d times",key,c1);
	}
	MPI_Finalize();
}
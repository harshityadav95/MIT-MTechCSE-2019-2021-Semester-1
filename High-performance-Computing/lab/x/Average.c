#include<stdio.h>
#include<mpi.h>
int main(int argc, char *argv[])
{
	int rank, size,m1,average,newaverage[10],Totalavg=0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int m,a[100],i,b[100],sum = 0;

	if(rank == 0)
	{
		printf("Enter no of elements\n");
		scanf("%d", &m);
		printf("Enter the elements\n");
		for(i=0;i<m*size;i++)
			scanf("%d", &a[i]);

	}
	MPI_Bcast(&m,1,MPI_INT, 0,MPI_COMM_WORLD);
	MPI_Scatter(&a[0], m, MPI_INT, &b[0],m , MPI_INT, 0, MPI_COMM_WORLD);
	
	//calculating sum
	for(i=0;i<m;i++)
	{
		sum = sum +b[i];		
	}
	printf("Sum is %d in process %d\n",sum, rank );
	
	//calculating average in each process
	average = sum/m;
	printf("Average is %d in process %d\n",average, rank );


	MPI_Gather(&average,1,MPI_INT,&newaverage[0],1,MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
	{
		for(i=0;i<size;i++)
	{
		Totalavg =  Totalavg + newaverage[i];
	}
	printf("New avg is %d\n", Totalavg/size);

	}
	
	

	MPI_Finalize();

}
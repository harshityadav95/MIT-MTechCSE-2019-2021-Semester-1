#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[])
{
	int size,rank;
	int a[100]={0};
	int range=100;
	MPI_Status status;
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		//MPI_Send(a,100,MPI_INT,1,0,MPI_COMM_WORLD);
		//MPI_Send(a,100,MPI_INT,2,1,MPI_COMM_WORLD);

	}
	if (rank==1)
	{
		int a[100]={0};
		//MPI_Recv(a,100,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		for (int i = 2; i <=50; ++i)
		{
			//printf("\n Checking for");
			for (int j = 2; j < i; ++j)
			{
				if(i%j==0)
					{a[i]=1;}
			}
						if (a[i]==0)
						{
							printf("%d ",i );
						}
		}
	}
	if (rank==2)
	{
		
		//MPI_Recv(a,100,MPI_INT,0,2,MPI_COMM_WORLD,&status);
		int a[100]={0};
		for (int i = 51; i <=100; ++i)
		{
			
			for (int j = 2; j < i; ++j)
			{
				if(i%j==0)
					{a[i]=1;}
				
			}
			if (a[i]==0)
						{
							printf("%d ",i );
						}
		}
	}

	MPI_Finalize();



	return 1;

}
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int size,rank;
	int a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int a2[600]={0};
	int a3[600]={0};
	int number_of_elements=20;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Bcast(&number_of_elements,1,MPI_INT,0,MPI_COMM_WORLD);  
	/*MPI_Bcast(void* data,     int count,    MPI_Datatype datatype,    int root,    MPI_Comm communicator)*/ 
	
	MPI_Scatter(&a[0],number_of_elements,MPI_INT,&a2[0],number_of_elements/size,MPI_INT,0,MPI_COMM_WORLD);

	/*(MPI_Scatter(void* send_data,int send_count,MPI_Datatype send_datatype,void* recv_data,int recv_count,MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)*/
    for (int i = 0; i < number_of_elements/size; ++i)
    {
    	//a2[i]=i;
    }
    MPI_Gather(&a2[0],number_of_elements/size,MPI_INT,&a3[0],number_of_elements*size,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
    	for (int i = 0; i < number_of_elements; ++i)
    	{
    		printf("%d--",a3[i] );
    	}
    }

	MPI_Finalize();
	return 0;
}
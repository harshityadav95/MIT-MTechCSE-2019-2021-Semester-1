#include<stdio.h>
#include<mpi.h>
#include<string.h>
void main(int argc,char *argv[])
{
    int rank,size,n,i,x,k,l,a[20],b[20],sum=0,sum0[10],sum1=0,sum2=0;
    double t1,t2;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    t1 = MPI_Wtime(); 
    if(rank == 0)
    {
	    printf("enter n:");
	    scanf("%d",&n);
	    printf("enter n * m elements:");
	    x=size*n;
	    for(i=0;i<x;i++)
	    {
		    //printf("%d", i);
		    a[i]=i+1;
	    }
}
    	
MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);
//int MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm ) 
//MPI_Scatter(&size,1,MPI_INT,&l,1,MPI_INT,0,MPI_COMM_WORLD);
//printf("%d %d\t", rank,k);
MPI_Scatter(&a[0],x/size,MPI_INT,&b[0],x/size,MPI_INT,0,MPI_COMM_WORLD);
/* MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)*/
	
for(i=0;i<x/size;i++)
	sum=sum+b[i];
	//printf("%d %d\t",rank,b[i]);

	sum=sum/(x/size);
	
 MPI_Gather(&sum,1,MPI_INT,&sum0[0],1,MPI_INT,0,MPI_COMM_WORLD);
 /*MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)
    */
 if(rank==0)
 {
 	for(i=0;i<size;i++)
	{
		
		sum1=sum1+sum0[i];
	}

 	printf("avg= %d", sum1/size );
 }
t2 = MPI_Wtime(); 
printf( "Elapsed time is %f\n", t2 - t1 ); 
 MPI_Finalize();


}
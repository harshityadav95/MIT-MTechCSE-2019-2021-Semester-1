#include<stdio.h>
#include<mpi.h>
#include<string.h>
void main(int argc,char *argv[])
{
    int rank,size,n,i,A[20],B[20],sum=0,sum0=0,sum1=0,sum2=0;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank == 0)
    {
        printf("Enter the number of elements of array\n");
        scanf("%d",&n);
        printf("Enter the elements of array\n");
        for(i=0;i<n;i++)
            scanf("%d",&A[i]);
        printf("\nThe array is:\n");
        MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Send(&A[n/2],n/2,MPI_INT,1,1,MPI_COMM_WORLD);
        for(i=0;i<n/2;i++)
            sum0=sum0+A[i];
        MPI_Recv(&sum2,1,MPI_INT,1,2,MPI_COMM_WORLD,&status);
        sum=sum0+sum2;
        printf("\nThe sum is %d :",sum);
    }
    else if(rank==1)
{
	MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
    //sending the complete size of the array
	MPI_Recv(&B[0],n/2,MPI_INT,0,1,MPI_COMM_WORLD,&status);
	//receiveng 
    for(i=0;i<n/2;i++)
		sum1=sum1+B[i];
	MPI_Send(&sum1,1,MPI_INT,0,2,MPI_COMM_WORLD);
}
MPI_Finalize();
}


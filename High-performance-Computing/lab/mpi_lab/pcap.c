#include<stdio.h>
#include<mpi.h>
int main(int argc, char *argv[])
{
	int rank, size,i,j,n,r;
	double t,o;
	char a[100],b[100],c[100];
	int p=1;
	MPI_Init(&argc, &argv);
	double w= MPI_Wtime();
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		printf("enter length of string\n");
		scanf("%d",&n);
		printf("enter string \n ");
		scanf("%s",a);
	}
	
	MPI_Scatter(a,1,MPI_CHAR,b,1,MPI_CHAR,0,MPI_COMM_WORLD);
	//MPI_Scan(b,c,p,MPI_CHAR,MPI_SUM,MPI_COMM_WORLD);
	
	for(i=0;i<rank+1;i++)
	printf("%s ",&b[0]);
	
	  // t= MPI_Wtime();
	  // o=t-w;
	// printf("  time : %f ms \n ",o);
	//   if(rank==0){
	
	// 	printf("final time: %f \n",o);
	// }
	//MPI_Barrier(MPI_COMM_WORLD);
	//MPI_Bcast(&o,1,MPI_INT,0,MPI_COMM_WORLD);
	//MPI_Reduce(&o,&r,1,MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);
	//MPI_Barrier(MPI_COMM_WORLD);
	
	
	MPI_Finalize();	
		
}

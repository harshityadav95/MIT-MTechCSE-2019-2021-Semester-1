#include<stdio.h>
#include<mpi.h>
#include<string.h>
int fact(int n)
{
	 if(n==0)
	return 1;
	else return n*fact(n-1);

}
void main(int argc,char *argv[])
{
int rank,i,size,b,c;
double t1,t2,t3,t4;
MPI_Status status;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
t1=MPI_Wtime();
for(i=0;i<size;i++)
{
	if(rank==i)
	{
		t3=MPI_Wtime();
		b=fact(rank+1);
		printf("Process of rank %d has factorial value %d for number %d\n",rank,b,rank+1);
		t4=MPI_Wtime();
		printf("MPI_Wtime measured the time taken by process %d to be %1.2f\n",rank,t4-t3);
	}
}
MPI_Scan(&b,&c,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
if(rank==size-1)
{
	printf("The sum is %d\n",c);
}
t2=MPI_Wtime();
printf("MPI_Wtime measured the time taken by process %d to be %1.2f\n",rank,t2-t1);
MPI_Finalize();

}


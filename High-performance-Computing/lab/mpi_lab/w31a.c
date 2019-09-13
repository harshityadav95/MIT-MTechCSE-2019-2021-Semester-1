#include<stdio.h>
#include<mpi.h>
#include<time.h>
void main(int argc,char* argv[])
{
clock_t t1,t2;
clock_t tf;
double pt1,pt2;
int myrank,size,i,a=1,b;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
t1=clock();
pt1 = MPI_Wtime();
for(i=1;i<=(myrank+1);i++)
	a=a*i;

MPI_Scan(&a,&b,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
pt2 = MPI_Wtime();
printf("Time consumed by process %d is %.10f\n",myrank,(pt2-pt1));
if(myrank==size-1)
{
	printf("Final Sum = %d\n",b);
	t2=clock();

tf=(t2 - t1);
printf("Time consumed by whole program is %.10f\n",((double)tf/CLOCKS_PER_SEC));

}
MPI_Finalize();
}

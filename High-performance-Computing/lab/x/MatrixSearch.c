#include<stdio.h>
#include<mpi.h>

void main(int argc,char* argv[])
{

int myrank,size,i,a[15],j,b[10],count=0,key,fcount=0;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
if(myrank==0)
{
	printf("Enter the 3X3 matrix\n");
	for(i=0;i<3*3;i++)
			scanf("%d",&a[i]);

	printf("Enter the key to be searched\n");
	scanf("%d",&key);

}
MPI_Bcast(&key,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Scatter(&a,3,MPI_INT,&b,3,MPI_INT,0,MPI_COMM_WORLD);

for(i=0;i<3;i++)
	//printf("%d\t",b[i]);
	if(key==b[i])
	count++;
//printf("\n\n");
MPI_Reduce(&count,&fcount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

if(myrank==0)
{
	printf("%d is occuring %d times\n",key,fcount);
}
MPI_Finalize();
}
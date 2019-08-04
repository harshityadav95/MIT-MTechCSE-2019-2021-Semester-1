#include<stdio.h>
#include<mpi.h>
#include<string.h>

void main(int argc,char *argv[])
{
int myrank,size,len,i;
char message[10];
char message1[10];
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

if(myrank == 0)
{
printf("Enter the word\n");
scanf("%s",message);

len = strlen(message);
len = len + 1;

MPI_Ssend(&len,1,MPI_INT,1,0,MPI_COMM_WORLD);
MPI_Ssend(message,len,MPI_CHAR,1,1,MPI_COMM_WORLD);

MPI_Recv(message1,len,MPI_CHAR,1,3,MPI_COMM_WORLD,&status);

printf("After toggling = %s\n",message1);
}
else if(myrank == 1)
{
MPI_Recv(&len,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
MPI_Recv(message1,len,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);

printf("Process of %d received the message %s\n",myrank,message1);

for(i=0; message1[i]!='\0'; i++)
{
if(message1[i] >= 'A' && message1[i] <= 'Z')
{
message1[i] = message1[i] + 'a' - 'A';
}
else if(message1[i] >= 'a' && message1[i] <= 'z')
{
message1[i] = message1[i] + 'A' - 'a';
}
}

MPI_Send(message1,len,MPI_CHAR,0,2,MPI_COMM_WORLD);

printf("Process of %d received the message %s\n",myrank,message1);
}
MPI_Finalize();
}


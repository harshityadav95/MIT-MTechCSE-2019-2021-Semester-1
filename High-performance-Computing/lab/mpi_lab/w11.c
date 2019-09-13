// week 1-1 using point to point commuinication
#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[])
{
    int Rank,Size;
    MPI_Init(&argc,&argv);

    //Size returns tht total number of process 
    //ranks are from 0 to size-1
    MPI_Comm_size(MPI_COMM_WORLD,&Size);
    MPI_Comm_rank(MPI_COMM_WORLD,&Rank);
    if(Rank==0)
    {
        int op1,op2;
        scanf("%d",&op1);
        scanf("%d",&op2);
        
            MPI_Send(&op1,1,MPI_INT,1,0,MPI_COMM_WORLD);
            MPI_Send(&op2,1,MPI_INT,1,1,MPI_COMM_WORLD);
        
            MPI_Send(&op1,1,MPI_INT,2,2,MPI_COMM_WORLD);
            MPI_Send(&op2,1,MPI_INT,2,3,MPI_COMM_WORLD);
        
            MPI_Send(&op1,1,MPI_INT,3,4,MPI_COMM_WORLD);
            MPI_Send(&op2,1,MPI_INT,3,5,MPI_COMM_WORLD);
        
            MPI_Send(&op1,1,MPI_INT,4,6,MPI_COMM_WORLD);
            MPI_Send(&op2,1,MPI_INT,4,7,MPI_COMM_WORLD);
        
        //Send: data+count+datatype +destination+tag+communicator
        //Receive : data+count+datatype+source+tag+communicator+status

    }
    else if(Rank==1)
    {
        int a,b,sub;
        MPI_Status status;
        
        MPI_Recv(&a,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(&b,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        sub=a-b;
        printf(" Subtraction : %d - %d = %d",a,b,sub);
    } 
     else if(Rank==2)
    {
        int a,b,sub;
        MPI_Status status;
        
        MPI_Recv(&a,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
        MPI_Recv(&b,1,MPI_INT,0,3,MPI_COMM_WORLD,&status);
        sub=a+b;
        printf(" Addition : %d - %d = %d",a,b,sub);
    }    
     else if(Rank==3)
    {
        int a,b,sub;
        MPI_Status status;
        
        MPI_Recv(&a,1,MPI_INT,0,4,MPI_COMM_WORLD,&status);
        MPI_Recv(&b,1,MPI_INT,0,5,MPI_COMM_WORLD,&status);
        sub=a*b;
        printf(" Multiplication : %d - %d = %d",a,b,sub);
    }    
     else if(Rank==4)
    {
        int a,b,sub;
        MPI_Status status;
        
        MPI_Recv(&a,1,MPI_INT,0,6,MPI_COMM_WORLD,&status);
        MPI_Recv(&b,1,MPI_INT,0,7,MPI_COMM_WORLD,&status);
        sub=a/b;
        printf(" Division : %d - %d = %d",a,b,sub);
    }       
    // If you dont add mpi finalise the program will run without displaying any output 
    MPI_Finalize();
    return 0;


}
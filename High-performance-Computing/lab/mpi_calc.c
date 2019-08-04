#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int Rank, Size;
    MPI_Init(&argc, &argv);
    // size returns the total number of process  
    MPI_Comm_size(MPI_COMM_WORLD, &Size);
    // rank returns the rank o that process
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);
    if (Rank == 0)
    {
        int operand1, operand2;
        printf("Enter First Operand.\n");
        scanf("%d", &operand1);
        printf("Enter Second Operand.\n");
        scanf("%d", &operand2);

        MPI_Send(&operand1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&operand2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

        MPI_Send(&operand1, 1, MPI_INT, 2, 3, MPI_COMM_WORLD);
        MPI_Send(&operand2, 1, MPI_INT, 2, 4, MPI_COMM_WORLD);

        MPI_Send(&operand1, 1, MPI_INT, 3, 5, MPI_COMM_WORLD);
        MPI_Send(&operand2, 1, MPI_INT, 3, 6, MPI_COMM_WORLD);

        MPI_Send(&operand1, 1, MPI_INT, 4, 7, MPI_COMM_WORLD);
        MPI_Send(&operand2, 1, MPI_INT, 4, 8, MPI_COMM_WORLD);
    }
    else if (Rank == 1)
    {
        int a, b, Sum;
        MPI_Status status;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        Sum = a + b;
        printf("process 1 :- %d + %d = %d\n", a, b, Sum);
    }
    else if (Rank == 2)
    {
        int a, b, Subtraction;
        MPI_Status status;
        MPI_Recv(&a, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
        Subtraction = a - b;
        printf("process 2 :- %d - %d = %d\n", a, b, Subtraction);
    }
    else if (Rank == 3)
    {
        int a, b, multiply;
        MPI_Status status;
        MPI_Recv(&a, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, 1, MPI_INT, 0, 6, MPI_COMM_WORLD, &status);
        multiply = a * b;
        printf("process 3 :- %d * %d = %d\n", a, b, multiply);
    }
    else if (Rank == 4)
    {
        int a, b, Divided;
        MPI_Status status;
        MPI_Recv(&a, 1, MPI_INT, 0, 7, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &status);
        Divided = a / b;
        printf("process 4 :- %d / %d = %d\n", a, b, Divided);
    }

    MPI_Finalize();
    return 0;
}

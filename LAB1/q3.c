#include<mpi.h>
#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]){
    int a = 5, b = 8;
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    printf("Process %d says: %d\n", rank, a+b);

     if(rank==1)
    printf("Process %d says: %d\n", rank, a-b);

     if(rank==2)
    printf("Process %d says: %d\n", rank, a*b);

     if(rank==3)
    printf("Process %d says: %d\n", rank, a/b);

    MPI_Finalize();
    // return 0;

    }
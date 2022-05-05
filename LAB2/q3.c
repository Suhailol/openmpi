#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE sizeof(int)

int main(int argc, char *argv[]){
    int size, rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *number = (int*)malloc(SIZE);
    if(rank == 0){
        *number = rand() % 10 + 1;
        for(int i=1; i<size; i++){
            printf("%d sent to %d from %d\n", *number, i, rank);
            MPI_Send(number, SIZE, MPI_INT, i, 100+i, MPI_COMM_WORLD);
        }}
    else{
        MPI_Recv(number, SIZE, MPI_INT, 0, 100+rank, MPI_COMM_WORLD, &status);
        printf("Recieved %d from 0 to %d\n", *number, rank);
    }
    MPI_Finalize();
    }

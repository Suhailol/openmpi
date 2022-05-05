#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size, fact, factsum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    fact = 1;
    for(int i = 0; i < rank+1; i++)
    fact = fact*i;

    MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if(rank)
    printf("Process %d say: \n", factsum);

    MPI_Finalize();
}
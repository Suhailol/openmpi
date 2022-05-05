#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    int rank, size;
    char str[6] = "HeLLo";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(str[rank] >= 'a' && str[rank] <= 'z'){
        str[rank] = str[rank] - 32;
    }
    else
        str[rank] = str[rank] + 32;
    
    printf("Process %d says %s\n", rank, str);
    MPI_Finalize();
}
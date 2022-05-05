#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size, N, a[10], b[10], c, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        N = size;
        fprintf(stdout,"Enter %d values: ");
        fflush(stdout);
        for(i=0; i<N; i++)
        scanf("%d", &a[i]);

    }
    MPI_Scatter(a, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout,"Recieved %d in Process %d\n", c, rank);
    fflush(stdout);

    int fact = 1;
    for(i=1; i<=c; i++){
        fact = fact*i;
    }
    MPI_Gather(&fact, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        fprintf(stdout, "The factorials are: ");
        for(i=0; i<N; i++){
        fprintf(stdout, "%d\t", b[i]);
        fflush(stdout);
        }

    }
    MPI_Finalize();
}
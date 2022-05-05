#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int N, rank, size, a[10], b[10], c, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
       N = size;
       fprintf(stdout, "Enter %d values: ", N);
       fflush(stdout);

       for(i=0; i < N; i++)
       scanf("%d", &a[i]);
    }
    MPI_Scatter(a, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
    fprintf(stdout, "I have recieved %d in process %d\n", c, rank);
    fflush(stdout);

    c = c*c;

    MPI_Gather(&c, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        fprintf(stdout, "the result gathered in the root is \n");
        fflush(stdout);
        for(i=0; i<N; i++){
            fprintf(stdout, "%d\t", b[i]);
            fflush(stdout);
        }
        // MPI_Finalize();
    }
     MPI_Finalize();
}
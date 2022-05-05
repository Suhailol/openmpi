#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char *argv[]){
    int rank, size, m;
    char str1[100], str2[100], concatted[100];
    char c1[100], c2[100];
    char b[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        fprintf(stdout, "Enter String 1: ");
        fflush(stdout);
        scanf("%s", str1);
        fprintf(stdout,"Enter String 2: ");
        fflush(stdout);
        scanf("%s", str2);

        m = strlen(str1)/size;
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str1, m, MPI_CHAR, c1, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2, m, MPI_CHAR, c2, m, MPI_CHAR, 0, MPI_COMM_WORLD);

    for(int i=0; i<2*m; i++){
        concatted[i] = c1[i/2];
        concatted[i+1] = c2[i/2];
    }
    concatted[2*m] = '\0';

    MPI_Gather(concatted, 2*m, MPI_CHAR, b, 2*m, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0){
        b[m*size*2] = '\0';
        fprintf(stdout, "Concatted: %s", b);
        fflush(stdout);
    }
    MPI_Finalize();
}
#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char *argv[]){
    int rank, size, n, l;
    int b[100] = {0};
    char str[100], c[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        n = size;
        printf("Enter a string: ");
        scanf("%s", &str);

        l = strlen(str)/n;
    }
    MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, 1, MPI_CHAR, c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    int count = 0;
    for(int i=0; i<l; i++){
        if(c[i]=='a' || c[i]=='e' || c[i]=='i' || c[i]=='o' || c[i] == 'u')
        continue;
    count += 1;
    }
    MPI_Gather(&count, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        int tcount = 0;
        for(int i=0; i<n; i++)
        tcount = tcount + b[i];
        fprintf(stdout, "The total number of non vowels = %d", tcount);
        fflush(stdout);
    }
    MPI_Finalize();
    
}
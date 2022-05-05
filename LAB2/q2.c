#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char word[5], y[5];
    int len = 5*sizeof(char);

    if(rank == 0 ){
        scanf("%s", word);
        MPI_Ssend(word, len, MPI_CHAR, 1, 101, MPI_COMM_WORLD);
        printf("%s sent from from Process %d\n", word, rank);
        MPI_Recv(word, len, MPI_CHAR, 1, 102, MPI_COMM_WORLD, &status);
        printf("Process 0 recieved: %s\n", word);        
    }
    else{
        MPI_Recv(y, len, MPI_CHAR, 0, 101, MPI_COMM_WORLD, &status);
        printf("Process 1 recieved %s\n", y);

        for(int i=0; i < strlen(y); i++){
            if(y[i]>='A' && y[i]<='Z'){
                y[i] = y[i] + 32;
            }
            else
                y[i] = y[i] - 32;
        }
        sleep(1);
        MPI_Ssend(y, len, MPI_CHAR, 0, 102, MPI_COMM_WORLD);
        printf("Process 1 sent %s\n", y);
    }
    MPI_Finalize();
}
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        int arr[5];
        for(int i=0; i<5; i++)
        scanf("%d", &arr[i]);
        
        for(int i=1; i<size; i++){
            MPI_Ssend(arr+i, sizeof(int), MPI_INT, i, 100+i, MPI_COMM_WORLD);
            printf("Process 0 sent %d to Process %d\n",arr[i], i);
        }
    }
    else{
        int num;
        MPI_Recv(&num, sizeof(int), MPI_INT, 0, 100+rank, MPI_COMM_WORLD, &status);
        // printf("Process %d: recieved %d from 0", rank, num);
        if(rank % 2 == 0){
            num = num*num;
        }
        else
        num = num*num*num;
        printf("Process %d: recieved %d from 0\n", rank, num);

    }
    MPI_Finalize();
}
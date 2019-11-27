#include <mpi.h>
#include <iostream>
#include "taskMPI11.h"

void taskMPI11::doTask11(int argc, char **argv) {
    int rank, size;

    MPI_Status st;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = 0;

    if (!rank) {
        MPI_Send(&data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }

    for (int i = 0; i < 10; i++) {
        MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &st);
        printf("from %d data = %d \n", rank, data++);
        MPI_Send(&data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
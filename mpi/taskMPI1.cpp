#include <iostream>
#include <mpi.h>
#include "taskMPI1.h"

void taskMPI1::doTask1() {
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello World! from %d of %d\n", rank, size);

    MPI_Finalize();
}

#include "taskMPI5.h"
#include <mpi.h>
#include <iostream>

void generateNotRandomArray5(int *array, int &num) {
    for (int i = 0; i < num; i++) {
        array[i] = i;
    }
}

void taskMPI5::doTask5(int argc, char **argv) {
    int NUM = 80;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a[NUM], b[NUM];
    int a1[NUM], b1[NUM];
    int n1 = NUM / size;
    generateNotRandomArray5(a, NUM);
    generateNotRandomArray5(b, NUM);

    MPI_Scatter(a, n1, MPI_INT, a1, n1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, n1, MPI_INT, b1, n1, MPI_INT, 0, MPI_COMM_WORLD);

    int localSum = 0;
    for (int i = 0; i < n1; i++) {
        localSum += a1[i] * b1[i];
    }
    printf("LOCAL is %d \n", localSum);

    if (rank) {
        MPI_Send(&localSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        int totalSum = localSum;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&localSum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSum = totalSum + localSum;
        }
        printf("TOTAL is %d \n", totalSum);
    }

    MPI_Finalize();
}

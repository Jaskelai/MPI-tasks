#include "taskMPI4.h"
#include <mpi.h>
#include <iostream>

void generatePositiveRandomArray(int *array, int &num) {
    for (int i = 0; i < num; i++) {
        array[i] = i + 1;
    }
}

void taskMPI4::doTask4(int argc, char **argv) {
    int NUM = 8;
    int array0[NUM];
    int rank, size;

    generatePositiveRandomArray(array0, NUM);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int array1[NUM];

    int n1 = NUM / size;

    MPI_Scatter(array0, n1, MPI_INT, array1, n1, MPI_INT, 0, MPI_COMM_WORLD);

    int localSum = 0;
    int localCounter = 0;
    for (int i = 0; i < n1; i++) {
        if (array1[i] > 0) {
            localCounter++;
            localSum += array1[i];
        }
    }
    printf("local sum is %d \n", localSum);
    int *localResult = new int[2];
    localResult[0] = localSum;
    localResult[1] = localCounter;

    if (rank) {
        MPI_Send(&localResult, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        int totalCounter = localResult[1];
        int totalSum = localResult[0];
        for (int i = 1; i < size; i++) {
            MPI_Recv(&localResult, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSum = totalSum + localResult[0];
            totalCounter = totalCounter + localResult[1];
        }
        printf("TOTAL is %d \n", totalSum);
        printf("NUM is %d \n", NUM);
        printf("RESULT IS %f", (double) totalSum / totalCounter);
    }

    MPI_Finalize();
}

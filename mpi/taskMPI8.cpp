#include "taskMPI8.h"
#include <mpi.h>
#include <random>
#include <ctime>

int generateRandomInt8(int &num) {
    return rand();
}

void taskMPI8::doTask8(int argc, char **argv) {
    int size, rank;
    int NUM = 88;
    int array[NUM];

    for (int i = 0; i < NUM; i++) {
        array[i] = generateRandomInt8(NUM);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int k = NUM / size;

    MPI_Barrier(MPI_COMM_WORLD);
    if (!rank) {
        for (int i = 0; i < NUM; i++) {
            printf("%d, ", array[i]);
        }
        printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if (!rank) {
        for (int i = 0; i < size; i++) {
            int localArray[k];
            int i1 = k * i;
            int i2 = k * (i + 1);
            if (rank == size - 1) i2 = NUM;
            int counter = 0;
            for (int j = i1; j < i2; j++) {
                localArray[counter] = array[j];
                counter++;
            }
            if (i != 0) {
                MPI_Send(&localArray, k, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    }

    int resultArray[k];
    if (!rank) {
        for (int i = 0; i < k; i++) {
            resultArray[i] = array[i];
        }
    } else {
        MPI_Recv(&resultArray, k, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    printf("Local from %d is: \n", rank);
    for (int i = 0; i < k; i++) {
        printf("%d, ", resultArray[i]);
    }
    printf("\n");
    if (rank) {
        MPI_Send(&resultArray, k, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    int totalArray[NUM];

    if (!rank) {
        int localResultArray[k];
        for (int i = 0; i < k; i++) {
            totalArray[i] = resultArray[i];
        }
        for (int i = 1; i < size; i++) {
            MPI_Recv(&localResultArray, k, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int counter = 0;
            for (int j = k * i; j < k * (i + 1); j++) {
                totalArray[j] = localResultArray[counter];
                counter++;
            }
        }
        for (int i = 0; i < NUM; i++) {
            printf("%d, ", totalArray[i]);
        }
    }


    MPI_Finalize();
}

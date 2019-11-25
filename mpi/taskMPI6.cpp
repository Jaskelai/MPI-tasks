#include "taskMPI6.h"
#include <mpi.h>
#include <random>
#include <ctime>

int generateRandomInt6(int &num) {
    return rand() % num;
}

void taskMPI6::doTask6(int argc, char **argv) {
    int size, rank;
    int NUM = 100;
    int matrix[NUM][NUM];

    int globalMinMax = 0;
    int globalMaxMin = 0;

    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            matrix[i][j] = generateRandomInt6(NUM);
        }
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *iterations = new int[size];
    int *intervals = new int[size];
    intervals[0] = 0;

    for (int i = 0; i < size; i++) {
        iterations[i] = NUM / size  + (i == 0 ? NUM % size : 0);
    }

    for (int i = 1; i < size; i++) {
        intervals[i] = intervals[i - 1] + iterations[i - 1];
    }

    int iterationsAll = intervals[rank];
    int buf[iterationsAll][NUM];

    MPI_Scatterv(matrix, iterations, intervals, MPI_INT, buf, iterationsAll, MPI_INT, 0, MPI_COMM_WORLD);

    int rowMax = 0;
    int maxMin = 0;
    int rowMin = INT_MAX;
    int minMax = INT_MAX;

    for (int i = 0; i < iterationsAll; i++) {
        for (int j = 0; j < NUM; j++) {
            if (buf[i][j] < rowMin) {
                rowMin = buf[i][j];
            }
            if (matrix[i][j] > rowMax) {
                rowMax = matrix[i][j];
            }
        }
        if (rowMin > maxMin) {
            maxMin = rowMin;
        }
        if (rowMax < minMax) {
            minMax = rowMax;
        }
    }

    int send_array[2];
    send_array[0] = minMax;
    send_array[1] = maxMin;

    if (!rank) {
        globalMinMax = send_array[0];
        globalMaxMin = send_array[1];
        for (int i = 1; i < size; i++) {
            MPI_Recv(&send_array, 2, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(&max_min, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (globalMinMax < send_array[0]) {
                globalMinMax = send_array[0];
            }
            if (globalMaxMin > send_array[1]) {
                globalMaxMin = send_array[1];
            }
        }
        printf("maxmin %d\n", globalMaxMin);
        printf("minmax %d", globalMinMax);
    } else {
        MPI_Send(&send_array, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

#include "taskMPI7.h"
#include <mpi.h>
#include <random>

int generateRandomInt7(int &num) {
    return rand() % num;
}

void taskMPI7::doTask7(int argc, char **argv) {
    int size, rank;
    int NUM = 30;
    int matrixSize = NUM * NUM;
    int matrix[matrixSize];

    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = generateRandomInt7(matrixSize);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *iterations = new int[size];
    int *intervals = new int[size];
    intervals[0] = 0;

    //сколько отправляем строк на каждый процесс
    for (int i = 0; i < size; i++) {
        iterations[i] = NUM / size  + (i == 0 ? NUM % size : 0);
    }

    //какой сдвиг на каждом из процессов
    for (int i = 1; i < size; i++) {
        intervals[i] = intervals[i - 1] + iterations[i - 1];
    }

    int iterationsAll = intervals[rank];
    int buf[NUM][intervals[rank]];

    MPI_Scatterv(matrix, iterations, intervals, MPI_INT, buf, iterationsAll, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Finalize();
}

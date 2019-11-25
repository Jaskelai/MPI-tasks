#include <mpi.h>
#include <ctime>
#include <random>
#include "taskMPI2.h"

void generateRandomArray(int *array, int &num) {
    srand(time(NULL));

    for (int i = 0; i < num; i++) {
        array[i] = rand();
    }
}

void generateNotRandomArray(int *array, int &num) {
    for (int i = 0; i < num; i++) {
        array[i] = i;
    }
}

void taskMPI2::doTask2(int argc, char *argv[]) {
    int NUM = 1500;
    int randomArray[NUM];
    int size, rank;
    int maxValueGlobal = INT_MIN;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {  //rank = 0
        generateRandomArray(randomArray, NUM);
    }

    MPI_Bcast(randomArray, NUM, MPI_INT, 0, MPI_COMM_WORLD);

    int k = NUM / size;
    int i1 = k * rank;
    int i2 = k * (rank + 1);
    if (rank == size - 1) i2 = NUM;
    int maxValueLocal = INT_MIN;
    for (int i = i1; i < i2; i++) {
        if (randomArray[i] > maxValueLocal) {
            maxValueLocal = randomArray[i];
        }
    }

    if (!rank) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&maxValueLocal, 2, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Max local value is %d \n", maxValueLocal);
            if (maxValueGlobal < maxValueLocal) {
                maxValueGlobal = maxValueLocal;
            }
        }
        printf("Max global value is %d", maxValueGlobal);
    } else {
        MPI_Send(&maxValueLocal, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

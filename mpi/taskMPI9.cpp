#include "taskMPI9.h"
#include <mpi.h>
#include <random>
#include <algorithm>

int generateRandomInt9(int &num) {
    return rand();
}

void taskMPI9::doTask9(int argc, char **argv) {
    int rank, numProc;
    int NUM = 40;
    int* arrayStart = new int[NUM];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
        for (int i = 0; i < NUM; i++) {
            arrayStart[i] = generateRandomInt9(NUM);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (!rank) {
        printf("START: \n");
        for (int i = 0; i < NUM; i++) {
            printf("%d, ", arrayStart[i]);
        }
        printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int *scount = new int[numProc];
    int *displs = new int[numProc];

    int size_min = NUM / numProc;
    int size_add = NUM % numProc;

    for (int i = 0; i < numProc; i++) {
        scount[i] = size_min + (i < size_add ? 1 : 0);
    }

    displs[0] = 0;
    for (int i = 1; i < numProc; i++) {
        displs[i] = displs[i - 1] + scount[i - 1];
    }

    int myCount = scount[rank];
    int* myArr = new int[myCount];

    MPI_Scatterv(arrayStart, scount, displs, MPI_INT, myArr, myCount, MPI_INT, 0, MPI_COMM_WORLD);

    std::reverse(myArr, myArr + myCount);

    int* arrayEnd = new int[NUM];

    std::reverse(displs, displs + numProc);

    MPI_Gatherv(myArr, myCount, MPI_INT, arrayEnd, scount, displs, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    if (!rank) {
        printf("END: \n");
        for (int i = 0; i < NUM; i++) {
            printf("%d, ", arrayEnd[i]);
        }
        printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
}

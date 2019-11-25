#include <mpi.h>
#include "taskMPI3.h"
#include <random>

void taskMPI3::doTask3(int argc, char **argv) {
    const int NUM = 20000;
    const int RADIUS = 100;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_real_distribution<double> uniform_dist(0, RADIUS);

    int k = NUM / size;
    int i1 = k * rank;
    int i2 = k * (rank + 1);
    if (rank == size - 1) i2 = NUM;
    int localCirclePointsCount = 0;

    for (int i = i1; i < i2; i++) {
        double x = uniform_dist(e1);
        double y = uniform_dist(e1);

        if (x * x + y * y <= RADIUS * RADIUS) {
            localCirclePointsCount++;
        }
    }

    if (rank) {
        MPI_Send(&localCirclePointsCount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (!rank) {
        int totalCirclePointsCount = localCirclePointsCount;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&localCirclePointsCount, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalCirclePointsCount = totalCirclePointsCount + localCirclePointsCount;
        }
        double resultPI = double (totalCirclePointsCount * 4) / NUM;
        printf("PI is %F", resultPI);
    }

    MPI_Finalize();
}

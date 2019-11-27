#include "taskMPI10.h"
#include <mpi.h>
#include <random>
#include <iostream>

void taskMPI10::doTask10(int argc, char **argv) {
    int rank, numProc;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    int n = 1000;
    int *buff = new int[n];
    MPI_Buffer_attach(buff, n * sizeof(int) + MPI_BSEND_OVERHEAD);

    for (int type = 1; type <= 4; type++) {
        if (rank == 0) {
            int *array1 = new int[n];
            for (int i = 0; i < n; i++) {
                array1[i] = rand() % 100 + 5;
            }
            int *array2 = new int[n];
            double t1 = MPI_Wtime();

            switch (type) {
                case 1: {
                    MPI_Send(array1, n, MPI_INT, 1, 0, MPI_COMM_WORLD);

                    MPI_Status st;
                    MPI_Recv(array2, n, MPI_INT, 1, 0, MPI_COMM_WORLD, &st);
                    break;
                }
                case 2: {
                    MPI_Ssend(array1, n, MPI_INT, 1, 0, MPI_COMM_WORLD);

                    MPI_Status st;
                    MPI_Recv(array2, n, MPI_INT, 1, 0, MPI_COMM_WORLD, &st);
                    break;
                }
                case 3: {

                    MPI_Bsend(array1, n, MPI_INT, 1, 0, MPI_COMM_WORLD);

                    MPI_Status st;
                    MPI_Recv(array2, n, MPI_INT, 1, 0, MPI_COMM_WORLD, &st);
                    break;
                }
                case 4: {
                    MPI_Rsend(array1, n, MPI_INT, 1, 0, MPI_COMM_WORLD);

                    MPI_Status st;
                    MPI_Recv(array2, n, MPI_INT, 1, 0, MPI_COMM_WORLD, &st);
                    break;
                }
            }

            double t2 = MPI_Wtime();


            std::cout << "type: " << type << " | time : " << t2 - t1 << std::endl;

            printf("\n");

        }
        if (rank == 1) {
            int *arr_send = new int[n];

            switch (type) {
                case 1: {
                    MPI_Status st;
                    MPI_Recv(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

                    MPI_Send(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    break;
                }
                case 2: {
                    MPI_Status st;
                    MPI_Recv(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

                    MPI_Ssend(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    break;
                }
                case 3: {
                    MPI_Status st;
                    MPI_Recv(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

                    MPI_Bsend(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    break;
                }
                case 4: {
                    MPI_Status st;
                    MPI_Recv(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

                    MPI_Rsend(arr_send, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    break;
                }
            }
        }
    }

    MPI_Finalize();
}
#include <iostream>
#include <omp.h>
#include "task2.h"

using namespace std;

void task2::doTask2() {
#pragma omp parallel num_threads(8)
    {
        int threadNumFirst = 3;
        printf("\nFirst region:\n");
#pragma omp parallel default(none) if (threadNumFirst > 2) num_threads(threadNumFirst)
        {
            printf("Current thread = %d, number of all threads = %d\n", omp_get_thread_num(),
                   omp_get_num_threads());
        }

        int threadNumSecond = 2;
        printf("\nSecond region:\n");
#pragma omp parallel default(none) if (threadNumSecond > 2) num_threads(threadNumSecond)
        {
            printf("Current thread = %d, number of all threads = %d\n", omp_get_thread_num(),
                   omp_get_num_threads());
        }
    }
}

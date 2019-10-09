#include <iostream>
#include <omp.h>
#include "task1.h"

using namespace std;

void task1::doTask1() {
#pragma omp parallel num_threads(8)
    {
        printf("Hello world, current thread = %d, number of all threads = %d\n", omp_get_thread_num(),
               omp_get_num_threads());
    }
}
#include <iostream>
#include <omp.h>
#include <zconf.h>
#include "task13.h"

void option1() {
    int currentThreadNum = 7;

#pragma omp parallel num_threads(8)
    {
        while (currentThreadNum >= 0) {
            if (omp_get_thread_num() == currentThreadNum) {
                printf("Current thread is %d \n", omp_get_thread_num());
                currentThreadNum--;
            }
        }
    }
}

void option2() {
#pragma omp parallel num_threads(8)
    {
        int nthreads = omp_get_num_threads();
        for (int i = nthreads - 1; i >= 0; i--) {
#pragma omp barrier
            {
                if (i == omp_get_thread_num()) {
#pragma omp critical
                    printf("Current thread is %d \n", i);
                }
            }
        }
    }
}

void option3() {
    omp_set_num_threads(8);
#pragma omp parallel
    for (int i = 7; i >= 0; i--) {
        if (omp_get_thread_num() != i) {
            sleep(1);
        } else {
            printf("Thread_num is  = %d\n", omp_get_thread_num());
        }
    }
}

void task13::doTask13() {
    option3();
}
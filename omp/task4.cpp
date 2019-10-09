#include <iostream>
#include <omp.h>
#include "task4.h"

int minimum(int array[], int size) {
    int min = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

int maximum(int array[], int size) {
    int max = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void task4::doTask4() {
    int a[] = {1, 5, 6, -5, 2, 4, 6, 9, 11, 20};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    omp_set_num_threads(2);
    int min;
    int max;

#pragma omp parallel
    {
#pragma omp master
        {
            min = minimum(a, 10);
            printf("thread is %d", omp_get_num_threads());
        }
#pragma omp single
        {
            max = maximum(b, 10);
            printf("thread is %d", omp_get_num_threads());
        }
    }

    printf("min of a = %d, max of b = %d\n", min, max);
}

#include <iostream>
#include <omp.h>
#include <ctime>
#include "task6.h"

int *generateArray(int size) {
    int *array = new int[size];
    std::srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
    return array;
}

void task6::doTask6() {
    int size = 100;
    int *array = generateArray(size);

    int sum1 = 0;
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        sum1 += array[i];
    }
    printf("Result for parallel for is %d \n", sum1 / size);

    int sum2 = 0;
#pragma omp parallel for reduction(+:sum2)
    for (int j = 0; j < size; j++) {
        sum2 += array[j];
    }

    printf("Result for parallel reduction is %d \n", sum2 / size);
}
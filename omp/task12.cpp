#include <iostream>
#include <ctime>
#include "task12.h"

int *generateRandArray(int size) {
    int *array = new int[size];
    std::srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
    return array;
}

void task12::doTask12() {
    int size = 1000;
    int *array = generateRandArray(size);
    int max = INT_MIN;

#pragma omp parallel for num_threads(4)
    for (int i = 0; i < size; i++) {
        if (array[i] % 7 == 0) {
#pragma omp critical
            if (array[i] > max) {
                max = array[i];
            }
        }
    }
    printf("Max is %d", max);
}
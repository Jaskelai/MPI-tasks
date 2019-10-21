#include <iostream>
#include <ctime>
#include "task11.h"

int *generateRandomArray(int size) {
    int *array = new int[size];
    std::srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand();
    }
    return array;
}

//atomic - делает атомарными операции с доступом/изменением переменной, соответственно не будет проблем при работе с переменной из разных потоков
void task11::doTask11() {
    int size = 30;
    int *array = generateRandomArray(size);
    int counter = 0;

#pragma omp parallel for num_threads(3)
    for (int i = 0; i < size; i++) {
        if (array[i] % 9 == 0) {
#pragma omp atomic
            counter++;
        }
    }
    printf("Counter is %d", counter);
}

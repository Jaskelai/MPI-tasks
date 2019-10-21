#include <iostream>
#include <omp.h>
#include <ctime>
#include "task10.h"

int **generateRandomMatrix(int rows, int columns) {
    int **array = new int *[rows];
    std::srand(time(NULL));

    for (int x = 0; x < rows; x++) {
        array[x] = new int[columns];
        for (int y = 0; y < columns; y++)
            array[x][y] = rand();
    }
    return array;
}

//critical - только один поток может выполнять эту секцию кода в данный момент времени, все остальные потоки будут заблокированы в ожидании, потом идет барьерная синхронизация потоков
//как synchronized в джаве
void task10::doTask10() {
    int rows = 6;
    int columns = 8;
    int **matrix = generateRandomMatrix(rows, columns);
    int min = INT_MAX;
    int max = INT_MIN;
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] <  min) {
#pragma omp critical
                min = matrix[i][j];
            }
            if (matrix[i][j] > max) {
#pragma omp critical
                max = matrix[i][j];
            }
        }
    }
    printf("Max is %d, Min is %d", max, min);
}
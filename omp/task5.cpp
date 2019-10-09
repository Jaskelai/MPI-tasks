#include <iostream>
#include <omp.h>
#include <ctime>
#include "task5.h"

int **generateMatrix(int rows, int columns) {
    int **array = new int *[rows];
    std::srand(time(NULL));

    for (int x = 0; x < rows; x++) {
        array[x] = new int[columns];
        for (int y = 0; y < columns; y++)
            array[x][y] = rand();
    }
    return array;
}

void task5::doTask5() {
    int rows = 5;
    int columns = 6;
    int **array = generateMatrix(rows, columns);

#pragma omp parallel sections
    {
#pragma omp section
        {
            int tempSum = 0;
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < columns; y++)
                    tempSum += array[x][y];
            }
            printf("Value is %d, thread number is %d \n", tempSum / (rows * columns), omp_get_thread_num());
        }
#pragma omp section
        {
            int min = array[0][0];
            int max = array[0][0];
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < columns; y++) {
                    if (array[x][y] < min) {
                        min = array[x][y];
                    }
                    if (array[x][y] > max) {
                        max = array[x][y];
                    }
                }
            }
            printf("Min is %d and max is %d,  thread number is %d \n", min, max, omp_get_thread_num());
        }
#pragma omp section
        {
            int counter = 0;
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < columns; y++)
                    if (array[x][y] % 3 == 0) {
                        counter++;
                    }
            }
            printf("Value is %d, thread number is %d \n", counter, omp_get_thread_num());
        }
    }

}

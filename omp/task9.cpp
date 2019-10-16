#include <iostream>
#include <omp.h>
#include "task9.h"

void task9::doTask9() {

    //где-то на тыще сто параллельный быстрее последовательного
    int rows = 1100;
    int columns = 1100;

    //define matrix
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = i + j;
        }
    }

    //define vector
    int *vector = new int[columns];
    for (int i = 0; i < columns; i++) {
        vector[i] = i;
    }

    int *result = new int[columns];

    //параллельная:
    double start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < columns; j++)
            result[i] += matrix[i][j] * vector[j];
    }
    double end = omp_get_wtime();

    printf("Parallel program:\nStart = %.30g\nEnd = %.30g\nDifference = %.30g\n",
           start, end, end - start);

    //последовательная
    start = omp_get_wtime();
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < columns; j++)
            result[i] += matrix[i][j] * vector[j];
    }
    end = omp_get_wtime();

    printf("Sequential program:\nStart = %.30g\nEnd = %.30g\nDifference = %.30g\n",
           start, end, end - start);
}

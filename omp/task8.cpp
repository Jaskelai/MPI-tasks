#include <iostream>
#include <omp.h>
#include "task8.h"

void task8::doTask8() {
    int n = 16000;
    int a[n];

    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    double b[n];

    omp_set_num_threads(8);
    double start = omp_get_wtime();
#pragma omp parallel for schedule(static, 100)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }
    double end = omp_get_wtime();

    printf("Start: %.40g End: %.40g, Static Difference = %.15g \n", start, end, end - start);

    start = omp_get_wtime();


    omp_set_num_threads(8);
    start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 100)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }
    end = omp_get_wtime();

    printf("Start: %.40g End: %.40g, Dynamic Difference = %.15g\n", start, end, end - start);

    //блок 1 - первый поток, блок 2 - второй поток..., размер блок уменьшается пропорционально осташимся итерациям и потокам, чтобы сбалансировать
    omp_set_num_threads(8);
    start = omp_get_wtime();
#pragma omp parallel for schedule(guided, 100)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }
    end = omp_get_wtime();

    printf("Start: %.40g End: %.40g, Guided Difference = %.15g\n", start, end, end - start);

    //тип распределения выбирается системой, способ выбирается в рантайме по значению OMP_SCHEDULE
    omp_set_num_threads(8);
    start = omp_get_wtime();
#pragma omp parallel for schedule(auto)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }
    end = omp_get_wtime();

    printf("Start: %.40g End: %.40g, Auto Difference = %.15g\n", start, end, end - start);
}
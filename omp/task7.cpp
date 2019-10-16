#include <iostream>
#include <omp.h>
#include "task7.h"

void task7::doTask7() {
    int a[12], b[12], c[12];

    //первый блок из 4 итераций выполняет 1 поток, 2 блок из 4 операций выполняет 2 поток
    omp_set_num_threads(3);
#pragma omp parallel for schedule(static, 3)
    for (int i = 0; i < 12; i++) {
        a[i] = i + 1;
        b[i] = i + 2;
        printf("a: %d, b: %d, thread_num %d from %d \n", a[i], b[i], omp_get_thread_num(), omp_get_num_threads());
    }

    //каждый поток получает по итерации, если размер блока > кол-во потоков, то оставшийся блок получают первые освободившиеся потоки
    int threads2 = 4;
#pragma omp parallel for schedule(dynamic, 3)
    for (int i = 0; i < 12; i++) {
        c[i] = a[i] + b[i];
        printf("c: %d, thread_num %d from %d \n", c[i], omp_get_thread_num(), omp_get_num_threads());
    }
}
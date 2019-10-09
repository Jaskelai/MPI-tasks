#include <iostream>
#include <omp.h>
#include "task3.h"

void task3::doTask3(){
    int a = 1;
    int b = 2;

    //private - свой экземпляр переменной для каждого потока, начальное значение не определено
    //firstprivate - начальное значение для каждой копии будет копироваться из главного потока
    printf("\nFirst region:\n");
#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        a = 0;
        printf("Current thread = %d\n", omp_get_thread_num());

        printf("a before = %d\n", a);
        a += omp_get_thread_num();
        printf(" a after = %d\n", a);

        printf("b before = %d\n", b);
        b += omp_get_thread_num();
        printf(" b after = %d\n", b);
    }

    printf("\nSecond region:\n");

    //shared - общая для всех потоков
#pragma omp parallel default(none) num_threads(4) shared(a) private(b)
    {
        b = 0;
        printf("Current thread = %d\n", omp_get_thread_num());

        printf("a before = %d\n", a);
        b -= omp_get_thread_num();
        printf("a after = %d\n", a);

        printf("b before = %d\n", b);
        b -= omp_get_thread_num();
        printf("b after = %d\n", b);
    }
}

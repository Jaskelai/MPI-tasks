#include <iostream>
#include <omp.h>

using namespace std;

void taskOne();

void taskTwo();

void taskThree();

int main() {
    taskOne();
    //taskTwo();
    //taskThree();
}

void taskOne() {
#pragma omp parallel default(none) num_threads(8)
    {
        printf("Hello world, current thread = %d, number of all threads = %d\n", omp_get_thread_num(),
               omp_get_num_threads());
    }
}

void taskTwo() {
    int threadNumFirst = 3;
    printf("\nFirst region:\n");
#pragma omp parallel default(none) if (threadNumFirst > 2) num_threads(threadNumFirst)
    {
        printf("Current thread = %d, number of all threads = %d\n", omp_get_thread_num(),
               omp_get_num_threads());
    }

    int threadNumSecond = 2;
    printf("\nSecond region:\n");
#pragma omp parallel default(none) if (threadNumSecond > 2) num_threads(threadNumSecond)
    {
        printf("Current thread = %d, number of all threads = %d\n", omp_get_thread_num(),
               omp_get_num_threads());
    }
}

//void taskThree() {
//    int a = 0;
//    int b = 0;
//
//#pragma omp parallel default(none) num_threads(2) private(a) firstprivate(b)
//    {
//        printf("Current thread = %d\n", omp_get_thread_num());
//
//        printf("a before = %d\n", a);
//        a += omp_get_thread_num();
//        printf("a after = %d\n", a);
//
//        printf("b before = %d\n", b);
//        b += omp_get_thread_num();
//        printf("b after = %d\n", b);
//    }
//
//    printf("\nSecond region:\n");
//
//#pragma omp parallel default(none) num_threads(4) shared(a) private(b)
//    {
//        printf("Current thread = %d\n", omp_get_thread_num());
//
//        printf("a before = %d\n", a);
//        b -= omp_get_thread_num();
//        printf("a after = %d\n", a);
//
//        printf("b before = %d\n", b);
//        b -= omp_get_thread_num();
//        printf("b after = %d\n", b);
//    }
//}

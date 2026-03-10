#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 10000000  // Növelt vektorhossz

// Szekvenciális skaláris szorzat
double scalar_product_sequential(int* A, int* B, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}

// Párhuzamos skaláris szorzat (OpenMP)
double scalar_product_parallel(int* A, int* B, int n) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}

int main() {
    int* A = (int*)malloc(N * sizeof(int));
    int* B = (int*)malloc(N * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }

    double total_sequential_time = 0.0;
    double total_parallel_time = 0.0;

    for (int i = 0; i < 100; i++) {
        double start_time = omp_get_wtime();
        scalar_product_sequential(A, B, N);
        double end_time = omp_get_wtime();
        total_sequential_time += (end_time - start_time);

        start_time = omp_get_wtime();
        scalar_product_parallel(A, B, N);
        end_time = omp_get_wtime();
        total_parallel_time += (end_time - start_time);
    }

    printf("Szekvenciális átlagos futási idő: %f másodperc\n", total_sequential_time / 100);
    printf("Párhuzamos átlagos futási idő: %f másodperc\n", total_parallel_time / 100);

    double speedup = total_sequential_time / total_parallel_time;
    printf("Gyorsulás: %f\n", speedup);

    int num_threads = omp_get_num_threads();
    double efficiency = speedup / num_threads;
    printf("Hatékonyság: %f\n", efficiency);

    free(A);
    free(B);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

#define N 1000000  // Tömb mérete
#define MAX_THREADS 4  // Maximális szálak száma

double* array;
double* results;  // Minden szál eredménye

// Szekvenciális szorzás
double sequential_product(double* array, int size) {
    double product = 1.0;
    for (int i = 0; i < size; i++) {
        product *= array[i];
    }
    return product;
}

// Rekurzív szorzás (maximális mélység)
double recursive_product(double* array, int start, int end, int depth) {
    if (end - start == 1) {  // Alap eset: egy elem szorzata
        return array[start];
    }
    if (depth <= 0) {
        return array[start] * array[start + 1];  // Ha elérjük a maximális mélységet, egyszerűen szorozzuk
    }

    int mid = (start + end) / 2;
    double left_product = recursive_product(array, start, mid, depth - 1);
    double right_product = recursive_product(array, mid, end, depth - 1);
    return left_product * right_product;
}

// POSIX szálakkal párhuzamos szorzás
void* thread_product(void* arg) {
    int thread_id = *(int*)arg;
    int num_elements_per_thread = N / MAX_THREADS;
    int start = thread_id * num_elements_per_thread;
    int end = (thread_id + 1) * num_elements_per_thread;

    double product = 1.0;
    for (int i = start; i < end; i++) {
        product *= array[i];
    }
    results[thread_id] = product;
    return NULL;
}

// Párhuzamos szorzás POSIX szálakkal
double parallel_product_posix() {
    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_product, &thread_ids[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double final_product = 1.0;
    for (int i = 0; i < MAX_THREADS; i++) {
        final_product *= results[i];
    }
    return final_product;
}

// OpenMP párhuzamos szorzás for ciklussal
double parallel_product_openmp() {
    double product = 1.0;
    #pragma omp parallel for reduction(*:product)
    for (int i = 0; i < N; i++) {
        product *= array[i];
    }
    return product;
}

// OpenMP redukciós operátor használata
double parallel_product_openmp_reduction() {
    double product = 1.0;
    #pragma omp parallel for reduction(*:product)
    for (int i = 0; i < N; i++) {
        product *= array[i];
    }
    return product;
}

int main() {
    array = (double*)malloc(N * sizeof(double));  // Dinamikusan allokált tömb
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        array[i] = (rand() % 100000) / 100000.0 + 0.1;  // Véletlenszerű valós számok generálása
    }

    // Szekvenciális szorzás mérése
    clock_t start_time = clock();
    double product_seq = sequential_product(array, N);
    clock_t end_time = clock();
    double execution_time_seq = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sequential execution time: %.6f seconds\n", execution_time_seq);

    // Rekurzív szorzás mérése
    start_time = clock();
    double product_recurse = recursive_product(array, 0, N, 10);
    end_time = clock();
    double execution_time_recurse = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Recursive execution time: %.6f seconds\n", execution_time_recurse);

    // POSIX szálakkal párhuzamos szorzás mérése
    results = (double*)malloc(MAX_THREADS * sizeof(double));
    start_time = clock();
    double product_posix = parallel_product_posix();
    end_time = clock();
    double execution_time_posix = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("POSIX threads execution time: %.6f seconds\n", execution_time_posix);

    // OpenMP párhuzamos szorzás mérése
    start_time = clock();
    double product_openmp = parallel_product_openmp();
    end_time = clock();
    double execution_time_openmp = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("OpenMP parallel execution time: %.6f seconds\n", execution_time_openmp);

    // OpenMP redukció mérése
    start_time = clock();
    double product_openmp_red = parallel_product_openmp_reduction();
    end_time = clock();
    double execution_time_openmp_red = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("OpenMP reduction execution time: %.6f seconds\n", execution_time_openmp_red);

    // Memória felszabadítása
    free(array);
    free(results);

    return 0;
}
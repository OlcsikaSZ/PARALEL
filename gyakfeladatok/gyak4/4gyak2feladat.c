#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>

#define N 1000000  // Tömb mérete
#define NUM_THREADS 4  // Szálak száma

double* arr;  // Tömb az adatok tárolására
double* arr_copy;  // Másolat a futási idők méréséhez

// CREW_PREFIX (Concurrent Read Exclusive Write) algoritmus
void CREW_PREFIX(double* arr, int n) {
    // Először párhuzamosan összeadjuk az egyes részeket
    #pragma omp parallel for
    for (int i = 1; i < n; i++) {
        arr[i] += arr[i - 1];
    }
}

// EREW_PREFIX (Exclusive Read Exclusive Write) algoritmus
void EREW_PREFIX(double* arr, int n) {
    // Az EREW elv szerint az összes szál kizárólag a saját részét olvashatja/írhatja
    for (int i = 1; i < n; i++) {
        arr[i] += arr[i - 1];
    }
}

// OPTIMAL_PREFIX algoritmus
void OPTIMAL_PREFIX(double* arr, int n) {
    // Első fázis: jobb oldali részek összegzése
    for (int i = 1; i < n; i *= 2) {
        #pragma omp parallel for
        for (int j = i; j < n; j++) {
            arr[j] += arr[j - i];
        }
    }
}

// POSIX szálas megoldás a prefix számításhoz
void* POSIX_thread_prefix(void* arg) {
    int id = *((int*)arg);
    int num_elements = N / NUM_THREADS;
    int start = id * num_elements;
    int end = (id == NUM_THREADS - 1) ? N : (id + 1) * num_elements;

    for (int i = start + 1; i < end; i++) {
        arr[i] += arr[i - 1];
    }
    pthread_exit(NULL);
}

// Főprogram
int main() {
    arr = (double*)malloc(N * sizeof(double));  // Dinamikusan allokált tömb
    arr_copy = (double*)malloc(N * sizeof(double));

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Véletlenszerű számok generálása
    }

    // MÉRÉS: CREW_PREFIX
    memcpy(arr_copy, arr, N * sizeof(double)); 
    clock_t start_time = clock();
    CREW_PREFIX(arr_copy, N);
    clock_t end_time = clock();
    double CREW_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("CREW_PREFIX execution time: %.6f seconds\n", CREW_time);

    // MÉRÉS: EREW_PREFIX
    memcpy(arr_copy, arr, N * sizeof(double));
    start_time = clock();
    EREW_PREFIX(arr_copy, N);
    end_time = clock();
    double EREW_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("EREW_PREFIX execution time: %.6f seconds\n", EREW_time);

    // MÉRÉS: OPTIMAL_PREFIX
    memcpy(arr_copy, arr, N * sizeof(double));
    start_time = clock();
    OPTIMAL_PREFIX(arr_copy, N);
    end_time = clock();
    double OPTIMAL_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("OPTIMAL_PREFIX execution time: %.6f seconds\n", OPTIMAL_time);

    // MÉRÉS: POSIX szálas megoldás
    memcpy(arr_copy, arr, N * sizeof(double));
    start_time = clock();
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, POSIX_thread_prefix, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    end_time = clock();
    double POSIX_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("POSIX threads execution time: %.6f seconds\n", POSIX_time);

    // Eredmények táblázata
    printf("\nMethod | Time (seconds)\n");
    printf("CREW_PREFIX   | %.6f\n", CREW_time);
    printf("EREW_PREFIX   | %.6f\n", EREW_time);
    printf("OPTIMAL_PREFIX| %.6f\n", OPTIMAL_time);
    printf("POSIX threads | %.6f\n", POSIX_time);

    // Szabadítsuk fel a memóriát
    free(arr);
    free(arr_copy);

    return 0;
}
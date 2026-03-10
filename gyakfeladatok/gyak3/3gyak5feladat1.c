#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 8  // Maximális szálak száma

// Globális változók
int *array;  // A tömb
long long total_sum = 0;  // Az összeg

// Az egyes szálak által számolt részösszegek tárolására
long long *partial_sums;

// Szálak által végzett összegzés
void* sum_part(void* arg) {
    int thread_id = *(int*)arg;
    int num_elements_per_thread = 1000000 / MAX_THREADS;  // Feltételezzük, hogy a tömb mérete 1000000
    int start = thread_id * num_elements_per_thread;
    int end = (thread_id + 1) * num_elements_per_thread;

    long long sum = 0;
    for (int i = start; i < end; i++) {
        sum += array[i];
    }

    partial_sums[thread_id] = sum;
    return NULL;
}

// A teljes tömb összegzését végezve a párhuzamos összegzéssel
void parallel_sum(int num_threads) {
    pthread_t threads[num_threads];
    int thread_ids[num_threads];
    partial_sums = (long long*)malloc(sizeof(long long) * num_threads);

    // Elindítjuk a szálakat
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_part, &thread_ids[i]);
    }

    // Megvárjuk a szálak befejezését
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Összeadjuk a részösszegeket
    total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        total_sum += partial_sums[i];
    }

    printf("Total sum: %lld\n", total_sum);
}

int main() {
    // A tömb inicializálása
    int n = 1000000;  // Tömb mérete
    array = (int*)malloc(n * sizeof(int));

    // Véletlenszerűen töltsük fel a tömböt
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100;  // Véletlenszerű számok 0 és 99 között
    }

    // Párhuzamos összegzés
    clock_t start_time = clock();
    parallel_sum(MAX_THREADS);
    clock_t end_time = clock();
    
    double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Parallel execution time with %d threads: %.6f seconds\n", MAX_THREADS, execution_time);

    // Felszabadítjuk az erőforrásokat
    free(array);
    free(partial_sums);

    return 0;
}
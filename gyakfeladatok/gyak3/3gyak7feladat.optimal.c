#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000000  // A tömb mérete
#define MAX_THREADS 8  // Maximális szálak száma

int* array;  // Bemeneti tömb
int* prefix;  // Prefix tömb

// Optimális prefix kiszámítás
void* optimal_prefix_sum(void* arg) {
    int thread_id = *(int*)arg;
    int num_elements_per_thread = N / MAX_THREADS;
    int start = thread_id * num_elements_per_thread;
    int end = (thread_id + 1) * num_elements_per_thread;

    // Prefix számítás ezen a szakaszon
    if (start == 0) {
        prefix[start] = array[start];
    } else {
        prefix[start] = prefix[start - 1] + array[start];
    }

    for (int i = start + 1; i < end; i++) {
        prefix[i] = prefix[i - 1] + array[i];
    }

    return NULL;
}

int main() {
    array = (int*)malloc(N * sizeof(int));  // Dinamikusan allokált tömb
    prefix = (int*)malloc(N * sizeof(int));  // Prefix tömb

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;  // Véletlenszerű számok generálása
    }

    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    clock_t start_time = clock();
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, optimal_prefix_sum, &thread_ids[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end_time = clock();

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Optimal execution time with %d threads: %.6f seconds\n", MAX_THREADS, execution_time);

    free(array);
    free(prefix);
    return 0;
}
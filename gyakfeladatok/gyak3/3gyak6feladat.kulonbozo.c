#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000000  // Tömb mérete
#define MAX_THREADS 8  // Maximális szálak száma

int* array;  // A tömb
pthread_mutex_t lock;  // Mutex a globális változó védelmére

// A szálak által végzett számolás
void* count_property(void* arg) {
    int thread_id = *(int*)arg;
    int num_elements_per_thread = N / MAX_THREADS;
    int start = thread_id * num_elements_per_thread;
    int end = (thread_id + 1) * num_elements_per_thread;

    int local_count = 0;
    for (int i = start; i < end; i++) {
        if (array[i] % 2 != 0) {  // Páratlan számok
            local_count++;
        }
    }

    pthread_mutex_lock(&lock);
    total_count += local_count;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    array = (int*)malloc(N * sizeof(int));  // Dinamikusan allokált tömb
    srand(time(NULL));

    // Véletlenszerű egész számok generálása
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;
    }

    pthread_mutex_init(&lock, NULL);

    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    clock_t start_time = clock();
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, count_property, &thread_ids[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Parallel execution time with %d threads: %.6f seconds\n", MAX_THREADS, execution_time);

    pthread_mutex_destroy(&lock);
    free(array);
    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 8

int *array;
long long total_sum = 0;

long long recursive_sum(int *arr, int start, int end) {
    if (end - start <= 1) {
        return arr[start];
    }

    int mid = (start + end) / 2;
    return recursive_sum(arr, start, mid) + recursive_sum(arr, mid, end);
}

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    int num_elements_per_thread = 1000000 / MAX_THREADS;
    int start = thread_id * num_elements_per_thread;
    int end = (thread_id + 1) * num_elements_per_thread;

    long long result = recursive_sum(array, start, end);
    total_sum += result;

    return NULL;
}

int main() {
    int n = 1000000;
    array = (int*)malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100;
    }

    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];

    clock_t start_time = clock();
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Total sum: %lld\n", total_sum);
    printf("Recursive execution time with %d threads: %.6f seconds\n", MAX_THREADS, execution_time);

    free(array);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000  // A tömb mérete

// Szekvenciális prefix kiszámítás
void sequential_prefix_sum(int* array, int* prefix, int size) {
    prefix[0] = array[0];
    for (int i = 1; i < size; i++) {
        prefix[i] = prefix[i - 1] + array[i];
    }
}

int main() {
    int* array = (int*)malloc(N * sizeof(int));  // Dinamikusan allokált tömb
    int* prefix = (int*)malloc(N * sizeof(int));  // Prefix tömb

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;  // Véletlenszerű számok generálása
    }

    clock_t start_time = clock();
    sequential_prefix_sum(array, prefix, N);  // Szekvenciális prefix kiszámítás
    clock_t end_time = clock();

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sequential execution time: %.6f seconds\n", execution_time);

    free(array);
    free(prefix);
    return 0;
}
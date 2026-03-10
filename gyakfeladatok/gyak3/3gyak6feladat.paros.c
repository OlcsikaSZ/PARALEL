#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000  // Tömb mérete

// Számolja meg, hány páros szám található a tömbben
int count_even(int* array, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int* array = (int*)malloc(N * sizeof(int));  // Dinamikusan allokált tömb
    srand(time(NULL));

    // Véletlenszerű egész számok generálása
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;  // 0-99 közötti számok
    }

    clock_t start_time = clock();
    int result = count_even(array, N);  // Szekvenciális számlálás
    clock_t end_time = clock();

    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Number of even numbers: %d\n", result);
    printf("Sequential execution time: %.6f seconds\n", execution_time);

    free(array);
    return 0;
}
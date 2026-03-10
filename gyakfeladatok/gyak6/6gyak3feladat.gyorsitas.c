#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int összehasonlítások = 0;
int másolások = 0;

void merge(int A[], int B[], int C[], int m, int n) {
    int i = 0, j = 0, k = 0;

    while (i < m && j < n) {
        összehasonlítások++;
        if (A[i] <= B[j]) {
            C[k++] = A[i++];
        } else {
            C[k++] = B[j++];
        }
        másolások++;
    }

    while (i < m) {
        C[k++] = A[i++];
        másolások++;
    }

    while (j < n) {
        C[k++] = B[j++];
        másolások++;
    }
}

int main() {
    int n = 100000;
    int* A = malloc(n * sizeof(int));
    int* B = malloc(n * sizeof(int));
    int* C = malloc(2 * n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand();
        B[i] = rand();
    }

    clock_t start = clock();
    merge(A, B, C, n, n);
    clock_t end = clock();

    double idő = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Ido: %.6f s\n", idő);
    printf("Osszehasonlitasok: %d\n", összehasonlítások);
    printf("Masolasok: %d\n", másolások);

    free(A);
    free(B);
    free(C);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int meretek[] = {1000, 2000, 4000, 8000};  // növelhető
    int darab = sizeof(meretek) / sizeof(meretek[0]);
    srand(time(NULL));

    for (int m = 0; m < darab; m++) {
        int n = meretek[m];
        int* arr = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 10000;

        clock_t start = clock();
        selection_sort(arr, n);
        clock_t end = clock();

        double ido = (double)(end - start) / CLOCKS_PER_SEC;
        printf("N = %d: Ido = %.6f masodperc\n", n, ido);

        free(arr);
    }

    return 0;
}

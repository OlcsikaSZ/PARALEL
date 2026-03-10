#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Iteratív függvények deklarálása
int sum_iterative(int arr[], int size);
int min_iterative(int arr[], int size);
int max_iterative(int arr[], int size);

// Rekurzív függvények deklarálása
int sum_recursive(int arr[], int size);
int min_recursive(int arr[], int size);
int max_recursive(int arr[], int size);

int main() {
    int n;

    // A tömb méretének beolvasása
    printf("Adja meg a tömb méretét: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));  // Dinamikusan foglalunk helyet a tömbnek

    // A tömb értékeinek beolvasása
    printf("Adja meg a tömb elemeit:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // A számítások méréséhez szükséges változók
    clock_t start, end;
    double time_taken;

    // Iteratív összeg számítása
    start = clock();
    int sum = sum_iterative(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iteratív összeg: %d (Idő: %f másodperc)\n", sum, time_taken);

    // Iteratív minimum számítása
    start = clock();
    int min_value = min_iterative(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iteratív minimum: %d (Idő: %f másodperc)\n", min_value, time_taken);

    // Iteratív maximum számítása
    start = clock();
    int max_value = max_iterative(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iteratív maximum: %d (Idő: %f másodperc)\n", max_value, time_taken);

    // Rekurzív összeg számítása
    start = clock();
    sum = sum_recursive(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Rekurzív összeg: %d (Idő: %f másodperc)\n", sum, time_taken);

    // Rekurzív minimum számítása
    start = clock();
    min_value = min_recursive(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Rekurzív minimum: %d (Idő: %f másodperc)\n", min_value, time_taken);

    // Rekurzív maximum számítása
    start = clock();
    max_value = max_recursive(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Rekurzív maximum: %d (Idő: %f másodperc)\n", max_value, time_taken);

    // Memória felszabadítása
    free(arr);

    return 0;
}

// Iteratív összeg
int sum_iterative(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Iteratív minimum
int min_iterative(int arr[], int size) {
    int min_value = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    return min_value;
}

// Iteratív maximum
int max_iterative(int arr[], int size) {
    int max_value = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
}

// Rekurzív összeg
int sum_recursive(int arr[], int size) {
    if (size == 0) {
        return 0;
    } else {
        return arr[size - 1] + sum_recursive(arr, size - 1);
    }
}

// Rekurzív minimum
int min_recursive(int arr[], int size) {
    if (size == 1) {
        return arr[0];
    } else {
        int min_rest = min_recursive(arr, size - 1);
        return (arr[size - 1] < min_rest) ? arr[size - 1] : min_rest;
    }
}

// Rekurzív maximum
int max_recursive(int arr[], int size) {
    if (size == 1) {
        return arr[0];
    } else {
        int max_rest = max_recursive(arr, size - 1);
        return (arr[size - 1] > max_rest) ? arr[size - 1] : max_rest;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define MAX_POINTS 1000  // Maximális pontszám a teszthez

// Lagrange interpoláció számítása
double lagrange_interpolation(double *x, double *y, double target, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (target - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

// Párhuzamos Lagrange interpoláció
double lagrange_interpolation_parallel(double *x, double *y, double target, int n) {
    double result = 0.0;
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (target - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    int n = 1000;  // Pontok száma
    double *x = (double*)malloc(n * sizeof(double));
    double *y = (double*)malloc(n * sizeof(double));

    // Véletlenszerű adatgenerálás
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        x[i] = rand() % 100;
        y[i] = sin(x[i]);  // Például sinus függvény a y értékekhez
    }

    double target = 50.0;  // Az interpolálni kívánt célérték

    // Szekvenciális interpoláció időzítése
    double start_time = omp_get_wtime();
    double result_sequential = lagrange_interpolation(x, y, target, n);
    double end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;
    printf("Szekvenciális eredmény: %f\n", result_sequential);
    printf("Szekvenciális futási idő: %f másodperc\n", sequential_time);

    // Párhuzamos interpoláció időzítése
    start_time = omp_get_wtime();
    double result_parallel = lagrange_interpolation_parallel(x, y, target, n);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("Párhuzamos eredmény: %f\n", result_parallel);
    printf("Párhuzamos futási idő: %f másodperc\n", parallel_time);

    // Gyorsulás számítása
    double speedup = sequential_time / parallel_time;
    printf("Gyorsulás: %f\n", speedup);

    // Hatékonyság számítása
    int num_threads = omp_get_num_threads();
    double efficiency = speedup / num_threads;
    printf("Hatékonyság: %f\n", efficiency);

    free(x);
    free(y);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define NUM_POINTS 1000000  // Intervallumok száma
#define A 0.0              // Integrálási tartomány alsó határa
#define B 1.0              // Integrálási tartomány felső határa
#define TRUE_VALUE 0.74682 // Ismert integrál érték: ∫(sin(x)/x)dx az [0,1] tartományban

// A függvény, amit integrálni kell
double f(double x) {
    return sin(x) / x;
}

// Szekvenciális téglalap módszer
double rectangle_method(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += func(a + i * h) * h;
    }
    return result;
}

// Párhuzamos téglalap módszer
double rectangle_method_parallel(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.0;
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        result += func(a + i * h) * h;
    }
    return result;
}

// Szekvenciális trapéz módszer
double trapezoidal_method(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; i++) {
        result += func(a + i * h);
    }
    result *= h;
    return result;
}

// Párhuzamos trapéz módszer
double trapezoidal_method_parallel(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    #pragma omp parallel for reduction(+:result)
    for (int i = 1; i < n; i++) {
        result += func(a + i * h);
    }
    result *= h;
    return result;
}

int main() {
    int n = NUM_POINTS;

    // Idő mérés szekvenciális módszerrel
    double start_time = omp_get_wtime();
    double result_rect = rectangle_method(f, A, B, n);
    double end_time = omp_get_wtime();
    double sequential_rect_time = end_time - start_time;

    start_time = omp_get_wtime();
    double result_trap = trapezoidal_method(f, A, B, n);
    end_time = omp_get_wtime();
    double sequential_trap_time = end_time - start_time;

    // Idő mérés párhuzamos módszerrel
    start_time = omp_get_wtime();
    double result_rect_parallel = rectangle_method_parallel(f, A, B, n);
    end_time = omp_get_wtime();
    double parallel_rect_time = end_time - start_time;

    start_time = omp_get_wtime();
    double result_trap_parallel = trapezoidal_method_parallel(f, A, B, n);
    end_time = omp_get_wtime();
    double parallel_trap_time = end_time - start_time;

    // Hiba számítása
    printf("Ismert integrál értéke: %.5f\n", TRUE_VALUE);
    printf("Szekvenciális téglalap eredmény: %.5f, hiba: %.5f\n", result_rect, fabs(result_rect - TRUE_VALUE));
    printf("Szekvenciális trapéz eredmény: %.5f, hiba: %.5f\n", result_trap, fabs(result_trap - TRUE_VALUE));
    printf("Párhuzamos téglalap eredmény: %.5f, hiba: %.5f\n", result_rect_parallel, fabs(result_rect_parallel - TRUE_VALUE));
    printf("Párhuzamos trapéz eredmény: %.5f, hiba: %.5f\n", result_trap_parallel, fabs(result_trap_parallel - TRUE_VALUE));

    // Futási idők és gyorsulás
    printf("\nFutási idők:\n");
    printf("Szekvenciális téglalap módszer: %.5f másodperc\n", sequential_rect_time);
    printf("Szekvenciális trapéz módszer: %.5f másodperc\n", sequential_trap_time);
    printf("Párhuzamos téglalap módszer: %.5f másodperc\n", parallel_rect_time);
    printf("Párhuzamos trapéz módszer: %.5f másodperc\n", parallel_trap_time);

    printf("\nGyorsulások:\n");
    printf("Téglalap módszer gyorsulása: %.2f\n", sequential_rect_time / parallel_rect_time);
    printf("Trapéz módszer gyorsulása: %.2f\n", sequential_trap_time / parallel_trap_time);

    // Hatékonyság számítása
    int num_threads = omp_get_num_threads();
    printf("\nTéglalap módszer hatékonysága: %.2f\n", (sequential_rect_time / parallel_rect_time) / num_threads);
    printf("Trapéz módszer hatékonysága: %.2f\n", (sequential_trap_time / parallel_trap_time) / num_threads);

    return 0;
}
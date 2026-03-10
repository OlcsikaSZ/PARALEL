#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Az INT_MAX deklarálásához
#include <math.h>

int main() {
    // Paraméterek
    int total_tasks = 3000;
    int time_machine1 = 10; // 1. gép feladat ideje
    int time_machine2 = 5;  // 2. gép feladat ideje
    int send_time = 2;      // küldési idő

    // Kezdeti feltételek
    int min_time = INT_MAX; // Most már elérhető az INT_MAX
    int optimal_n = 0;
    int optimal_m = 0;

    // Számítás a különböző n értékekhez
    for (int n = 0; n <= total_tasks; n++) {
        int m = total_tasks - n; // m = 3000 - n
        
        // Első gép ideje (számítás + küldés)
        int T1 = time_machine1 * n + send_time * m;
        
        // Második gép ideje (csak számítás)
        int T2 = time_machine2 * m;
        
        // Összes idő (a két gép közötti párhuzamos futtatás maximális ideje)
        int total_time = fmax(T1, T2);
        
        // Ha ez jobb, mint a legjobb eddigi idő, akkor tároljuk
        if (total_time < min_time) {
            min_time = total_time;
            optimal_n = n;
            optimal_m = m;
        }
    }

    // Eredmények kiírása
    printf("Optimális feladatok száma az 1. gépen: %d\n", optimal_n);
    printf("Optimális feladatok száma a 2. gépen: %d\n", optimal_m);
    printf("Minimalizált teljes idő: %d\n", min_time);

    // Opció: Grafikon adatok tárolása fájlba (CSV formátumban)
    FILE *f = fopen("time_chart.csv", "w");
    if (f == NULL) {
        printf("Hiba a fájl megnyitásakor.\n");
        return 1;
    }

    // Fejléc írása a CSV fájlba
    fprintf(f, "Feladatok az 1. gépen,Teljes idő\n");

    // Idő adatainak mentése
    for (int n = 0; n <= total_tasks; n++) {
        int m = total_tasks - n;
        int T1 = time_machine1 * n + send_time * m;
        int T2 = time_machine2 * m;
        int total_time = fmax(T1, T2);
        fprintf(f, "%d,%d\n", n, total_time);
    }

    fclose(f);
    printf("A grafikon adatokat elmentettük 'time_chart.csv' fájlba.\n");

    return 0;
}
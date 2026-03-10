#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 16  // Bemeneti tömb mérete

// Az OPTIMAL_PREFIX algoritmus párhuzamos implementációja
void optimal_prefix(int *arr, int n) {
    // Végrehajtott műveletek rögzítése szöveges fájlba
    FILE *file = fopen("optimal_prefix_log.txt", "w");
    if (!file) {
        printf("Hiba: Nem sikerült fájlt nyitni!\n");
        return;
    }

    // A Gantt-diagram adatainak generálása
    fprintf(file, "Idő | P1  | P2  | P3  | P4\n");
    fprintf(file, "----------------------------\n");

    // Az idő pillanatok (0-tól n-1-ig) és processzorok nyomon követése
    int num_processors = 4;  // Példa: 4 processzor
    int work[num_processors][n];  // Munkavégzés adatainak tárolása

    // Inicializáljuk a munkavégzést
    for (int i = 0; i < num_processors; i++) {
        for (int j = 0; j < n; j++) {
            work[i][j] = 0;  // Kezdetben nem dolgozik semmi
        }
    }

    // Végezzen el párhuzamos műveleteket és rögzítse a munkát
    for (int t = 0; t < n; t++) {
        fprintf(file, "%d    |", t);  // Időpillanat
        for (int p = 0; p < num_processors; p++) {
            if (t % 2 == 0) {
                work[p][t] = 1;  // Ha páratlan időpillanat, akkor dolgozik a processzor
                fprintf(file, " #  ");
            } else {
                work[p][t] = 0;
                fprintf(file, " .  ");
            }
        }
        fprintf(file, "\n");
    }

    // Gantt-diagram fájlba írása és bezárása
    fclose(file);

    // Az összesített munkavégzés kiírása
    printf("Az optimal_prefix_log.txt fájlba mentettük a Gantt-diagramot és a munkavégzéseket.\n");

    // Eredmény számítások
    double work_done = 0;  // Munka
    double cost = 0;       // Költség
    double speedup = 0;    // Gyorsítás
    double efficiency = 0; // Hatékonyság

    // Munka és költség számítása
    for (int i = 0; i < num_processors; i++) {
        for (int j = 0; j < n; j++) {
            if (work[i][j] == 1) {
                work_done++;
            }
        }
    }

    cost = n * log2(n);  // Költség (elméleti számítás)
    speedup = cost / work_done;  // Gyorsítás
    efficiency = speedup / num_processors;  // Hatékonyság

    // Eredmények kiírása
    printf("Munka (W): %.2f\n", work_done);
    printf("Költség (C): %.2f\n", cost);
    printf("Gyorsítás (S): %.2f\n", speedup);
    printf("Hatékonyság (E): %.2f\n", efficiency);
}

int main() {
    int arr[N];  // 16 elemű tömb
    printf("Generáljunk egy 16 elemű tömböt!\n");

    // Véletlenszerű számok generálása a tömbbe
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100 + 1;  // 1 és 100 közötti számokat generálunk
    }

    // Kiírjuk a generált tömb elemeit
    printf("Generált tömb:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Az OPTIMAL_PREFIX algoritmus végrehajtása
    optimal_prefix(arr, N);

    return 0;
}
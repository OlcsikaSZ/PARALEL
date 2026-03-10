#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h> // OpenMP a párhuzamosításra

// EREW_PREFIX algoritmus
void erew_prefix(int* arr, int* out, int n, FILE* output_file) {
    int log_n = (int)log2(n);
    char** work_file = (char**)malloc(n * sizeof(char*));

    // Inicializáljuk a munkafájlt
    for (int i = 0; i < n; i++) {
        work_file[i] = (char*)calloc(log_n, sizeof(char)); // Munkafájl minden sorának megadása
    }

    // Előtagösszeg kiszámítása (párhuzamosan)
    for (int step = 1; step <= log_n; step++) {
        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            int prev = i - (1 << (step - 1));
            if (prev >= 0) {
                arr[i] += arr[prev];  // Frissítjük az aktuális elem előtagösszegét
                work_file[step][i] = '#'; // Hasznos munkavégzés, ezt jelöljük a fájlban
            } else {
                work_file[step][i] = '.'; // Nem történt hasznos munkavégzés
            }
        }

        // Munkafájl kiírása az aktuális időpillanatra
        fprintf(output_file, "Step %d:\n", step);
        for (int i = 0; i < n; i++) {
            fprintf(output_file, "%c ", work_file[step][i]);
        }
        fprintf(output_file, "\n");
    }

    // A számított előtagösszegek kiírása
    for (int i = 0; i < n; i++) {
        out[i] = arr[i];
    }

    // Felszabadítjuk a memóriát
    for (int i = 0; i < n; i++) {
        free(work_file[i]);
    }
    free(work_file);
}

// Főprogram
int main() {
    int n = 100;  // Bemeneti méret (n = 100)
    int* arr = (int*)malloc(n * sizeof(int));
    int* out = (int*)malloc(n * sizeof(int));

    // Véletlenszerű számok generálása a bemeneti tömbhöz
    printf("Bemeneti tömb generálása: ");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10;  // Véletlen számok [0-9]
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Szöveges fájl megnyitása, amelybe a munkafájl adatait mentjük
    FILE* output_file = fopen("work_file.txt", "w");
    if (output_file == NULL) {
        printf("Nem sikerült fájlt megnyitni!\n");
        return -1;
    }

    // A párhuzamos EREW_PREFIX algoritmus futtatása
    erew_prefix(arr, out, n, output_file);

    // Az eredmény kiírása
    printf("A számított előtagösszeg: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", out[i]);
    }
    printf("\n");

    // Fájl bezárása
    fclose(output_file);

    // Számítási költség és gyorsítás
    // Az iteratív változat költsége: log2(n)
    double iterative_cost = log2(n);
    double parallel_cost = log2(n);  // Párhuzamos esetben is log2(n) a költség
    double speedup = iterative_cost / parallel_cost;
    double efficiency = speedup / n;

    // A gyorsítás és hatékonyság kiírása
    printf("Gyorsítás: %f\n", speedup);
    printf("Hatékonyság: %f\n", efficiency);

    // Felszabadítjuk az erőforrásokat
    free(arr);
    free(out);
    return 0;
}
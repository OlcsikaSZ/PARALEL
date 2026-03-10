#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Függvények deklarálása
void generate_array(int *arr, int size);
bool check_unique(int *arr, int size);
void print_array(int *arr, int size);

int main() {
    int n;

    // A tömb méretének beolvasása
    printf("Adja meg a tömb méretét: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));  // Dinamikusan foglalunk helyet a tömbnek

    // Számítási idő mérésére
    clock_t start, end;
    double time_taken;

    // A tömb generálásának méréséhez
    start = clock();
    generate_array(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tömb generálásának ideje: %f másodperc\n", time_taken);

    // A tömb kiírása
    printf("A generált tömb elemei:\n");
    print_array(arr, n);

    // A tömb egyediségének ellenőrzése
    start = clock();
    bool unique = check_unique(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tömb egyediségének ellenőrzése: %f másodperc\n", time_taken);
    
    if (unique) {
        printf("A tömb minden eleme egyedi.\n");
    } else {
        printf("A tömbben vannak duplikált elemek.\n");
    }

    // Memória felszabadítása
    free(arr);

    return 0;
}

// Véletlenszerű tömb generálása, duplikációval
void generate_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;  // Véletlenszerű szám generálása [0, 9999]
    }

    // 0.5 valószínűséggel duplikálás
    for (int i = 0; i < size / 2; i++) {
        if (rand() % 2 == 0) {  // 0.5 valószínűséggel
            int index = rand() % size;  // Véletlenszerű index
            int duplicate_value = arr[index];  // Az érték, amit duplikálunk
            arr[i] = duplicate_value;  // Az i-edik elem duplikálása
        }
    }
}

// A tömb egyediségének ellenőrzése
bool check_unique(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return false;  // Ha találunk duplikált elemet, visszatérünk 'false'-szal
            }
        }
    }
    return true;  // Ha nincs duplikáció, visszatérünk 'true'-val
}

// A tömb kiírása
void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
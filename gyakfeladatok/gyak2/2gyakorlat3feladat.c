#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Függvények deklarálása
void generate_array(float *arr, int size);
bool is_strictly_increasing(float *arr, int size);
int binary_search_iterative(float *arr, int size, float key);
int binary_search_recursive(float *arr, int left, int right, float key);
void print_array(float *arr, int size);

int main() {
    int n;
    float key;

    // A tömb méretének beolvasása
    printf("Adja meg a tömb méretét: ");
    scanf("%d", &n);

    // A keresett érték beolvasása
    printf("Adja meg a keresett értéket: ");
    scanf("%f", &key);

    // Dinamikus memóriafoglalás a tömb számára
    float *arr = (float *)malloc(n * sizeof(float));

    // Számítási idő mérésére
    clock_t start, end;
    double time_taken;

    // A tömb generálása
    start = clock();
    generate_array(arr, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tömb generálásának ideje: %f másodperc\n", time_taken);

    // A tömb kiírása
    printf("A generált tömb elemei:\n");
    print_array(arr, n);

    // A tömb szigorú növekvőségének ellenőrzése
    if (is_strictly_increasing(arr, n)) {
        printf("A tömb szigorúan monoton növekvő.\n");
    } else {
        printf("A tömb nem szigorúan monoton növekvő.\n");
    }

    // Iteratív bináris keresés
    start = clock();
    int index_iter = binary_search_iterative(arr, n, key);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iteratív keresés ideje: %f másodperc\n", time_taken);
    if (index_iter != -1) {
        printf("Az érték megtalálva az iteratív kereséssel, index: %d\n", index_iter);
    } else {
        printf("Az érték nem található az iteratív kereséssel.\n");
    }

    // Rekurzív bináris keresés
    start = clock();
    int index_rec = binary_search_recursive(arr, 0, n - 1, key);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Rekurzív keresés ideje: %f másodperc\n", time_taken);
    if (index_rec != -1) {
        printf("Az érték megtalálva a rekurzív kereséssel, index: %d\n", index_rec);
    } else {
        printf("Az érték nem található a rekurzív kereséssel.\n");
    }

    // Memória felszabadítása
    free(arr);

    return 0;
}

// Véletlenszerű tömb generálása, szigorúan monoton növekvő
void generate_array(float *arr, int size) {
    arr[0] = (float)(rand() % 1000);  // Az első elem véletlen
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + (float)(rand() % 100) / 10.0;  // Az előző elemhez hozzáadunk egy pozitív számot
    }
}

// Ellenőrzi, hogy a tömb szigorúan monoton növekvő
bool is_strictly_increasing(float *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] <= arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Iteratív bináris keresés
int binary_search_iterative(float *arr, int size, float key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;  // Ha nem találjuk, akkor -1-et adunk vissza
}

// Rekurzív bináris keresés
int binary_search_recursive(float *arr, int left, int right, float key) {
    if (left > right) {
        return -1;  // Ha már nincs több elem, akkor nem találtuk meg
    }
    int mid = left + (right - left) / 2;
    if (arr[mid] == key) {
        return mid;
    }
    if (arr[mid] < key) {
        return binary_search_recursive(arr, mid + 1, right, key);
    } else {
        return binary_search_recursive(arr, left, mid - 1, key);
    }
}

// A tömb kiírása
void print_array(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);  // A lebegőpontos számokat két tizedesjegy pontossággal kiírjuk
    }
    printf("\n");
}
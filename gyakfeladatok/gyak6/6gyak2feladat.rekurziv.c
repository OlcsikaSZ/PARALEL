#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define KIS_MERET 50  // ha kisebb, akkor nem párhuzamosítunk

typedef struct {
    int* arr;
    int bal;
    int jobb;
} Param;

void selection_sort(int arr[], int bal, int jobb) {
    for (int i = bal; i <= jobb - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j <= jobb; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void merge(int arr[], int bal, int kozep, int jobb) {
    int n1 = kozep - bal + 1;
    int n2 = jobb - kozep;

    int* bal_arr = malloc(n1 * sizeof(int));
    int* jobb_arr = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) bal_arr[i] = arr[bal + i];
    for (int j = 0; j < n2; j++) jobb_arr[j] = arr[kozep + 1 + j];

    int i = 0, j = 0, k = bal;
    while (i < n1 && j < n2) {
        if (bal_arr[i] <= jobb_arr[j]) arr[k++] = bal_arr[i++];
        else arr[k++] = jobb_arr[j++];
    }

    while (i < n1) arr[k++] = bal_arr[i++];
    while (j < n2) arr[k++] = jobb_arr[j++];

    free(bal_arr);
    free(jobb_arr);
}

void* parhuzamos_rendezes(void* arg);

void rendez(int arr[], int bal, int jobb) {
    if (jobb - bal + 1 <= KIS_MERET) {
        selection_sort(arr, bal, jobb);
        return;
    }

    int kozep = (bal + jobb) / 2;

    pthread_t szal1, szal2;
    Param p1 = {arr, bal, kozep};
    Param p2 = {arr, kozep + 1, jobb};

    pthread_create(&szal1, NULL, parhuzamos_rendezes, &p1);
    pthread_create(&szal2, NULL, parhuzamos_rendezes, &p2);

    pthread_join(szal1, NULL);
    pthread_join(szal2, NULL);

    merge(arr, bal, kozep, jobb);
}

void* parhuzamos_rendezes(void* arg) {
    Param* p = (Param*) arg;
    rendez(p->arr, p->bal, p->jobb);
    return NULL;
}

int main() {
    int n = 20000;
    int* arr_seq = malloc(n * sizeof(int));
    int* arr_par = malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int v = rand() % 10000;
        arr_seq[i] = arr_par[i] = v;
    }

    // Szekvenciális
    clock_t start_seq = clock();
    selection_sort(arr_seq, 0, n - 1);
    clock_t end_seq = clock();
    double ido_seq = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

    // Párhuzamos
    clock_t start_par = clock();
    Param foparam = {arr_par, 0, n - 1};
    parhuzamos_rendezes(&foparam);
    clock_t end_par = clock();
    double ido_par = (double)(end_par - start_par) / CLOCKS_PER_SEC;

    printf("Szekvencialis ido: %.6f s\n", ido_seq);
    printf("Parhuzamos ido: %.6f s\n", ido_par);

    free(arr_seq);
    free(arr_par);
    return 0;
}
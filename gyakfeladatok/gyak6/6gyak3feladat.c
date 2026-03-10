#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MERET 10

int tomb[MERET];

typedef struct {
    int* resz_tomb;
    int kezd, veg;
} Param;

void beszuro_rendezes_resz(int* tomb, int kezd, int veg) {
    int i, kulcs, j;
    for (i = kezd + 1; i <= veg; i++) {
        kulcs = tomb[i];
        j = i - 1;
        while (j >= kezd && tomb[j] > kulcs) {
            tomb[j + 1] = tomb[j];
            j--;
        }
        tomb[j + 1] = kulcs;
    }
}

void* rendez_szalas(void* arg) {
    Param* p = (Param*) arg;
    beszuro_rendezes_resz(tomb, p->kezd, p->veg);
    pthread_exit(NULL);
}

void osszefesul(int* eredmeny) {
    int i = 0, j = 5, k = 0;
    while (i < 5 && j < 10) {
        if (tomb[i] < tomb[j])
            eredmeny[k++] = tomb[i++];
        else
            eredmeny[k++] = tomb[j++];
    }
    while (i < 5) eredmeny[k++] = tomb[i++];
    while (j < 10) eredmeny[k++] = tomb[j++];
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < MERET; i++)
        tomb[i] = rand() % 100;

    printf("Eredeti tomb: ");
    for (int i = 0; i < MERET; i++) printf("%d ", tomb[i]);
    printf("\n");

    pthread_t szal1, szal2;
    Param p1 = {tomb, 0, 4};
    Param p2 = {tomb, 5, 9};

    clock_t kezdes = clock();

    pthread_create(&szal1, NULL, rendez_szalas, &p1);
    pthread_create(&szal2, NULL, rendez_szalas, &p2);
    pthread_join(szal1, NULL);
    pthread_join(szal2, NULL);

    int vegso[MERET];
    osszefesul(vegso);

    clock_t vege = clock();
    double ido = (double)(vege - kezdes) / CLOCKS_PER_SEC;

    printf("Rendezett tomb: ");
    for (int i = 0; i < MERET; i++) printf("%d ", vegso[i]);
    printf("\nIdo: %.6f masodperc\n", ido);

    return 0;
}

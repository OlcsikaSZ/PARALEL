#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void beszuro_rendezes(int tomb[], int meret);

int main() {
    int meretek[] = {10, 50, 100, 200, 300, 400, 500};
    int darab = sizeof(meretek) / sizeof(meretek[0]);
    srand(time(NULL));

    for (int k = 0; k < darab; k++) {
        int meret = meretek[k];
        int tomb[meret];
        for (int i = 0; i < meret; i++)
            tomb[i] = rand() % 1000;

        clock_t kezdes = clock();
        beszuro_rendezes(tomb, meret);
        clock_t vege = clock();

        double ido = (double)(vege - kezdes) / CLOCKS_PER_SEC;
        printf("Elemek: %d, Ido: %.6f masodperc\n", meret, ido);
    }

    return 0;
}
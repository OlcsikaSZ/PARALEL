#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int random_int = 500 + rand() % (1000 - 500 + 1);

    printf("Véletlen egész szám: %d\n", random_int);

    return 0;
}
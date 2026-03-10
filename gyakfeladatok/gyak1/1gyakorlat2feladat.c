#include <stdio.h>

int main() {
    // Számok, amiket ki szeretnénk írni
    int numbers[] = {123, 45, 6789, 1, 99999};
    int i;

    // A számok kiíratása 8 karakteres formátumban, jobbra igazítva
    for (i = 0; i < 5; i++) {
        printf("%08d\n", numbers[i]);  // 0-val kitöltve, 8 karakter szélesség
    }

    return 0;
}
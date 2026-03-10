#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Hiba: Két egész számot kell megadni argumentumként!\n");
        return 1;
    }

    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    if (min > max) {
        printf("Hiba: Az első számnak kisebbnek kell lennie, mint a második szám!\n");
        return 1; 
    }

    srand(time(NULL));

    int random_number = min + rand() % (max - min + 1);

    printf("A generált véletlen szám: %d\n", random_number);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_numbers(const char *filename, int num_elements) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Hiba a fájl megnyitásakor");
        exit(1);
    }

    for (int i = 0; i < num_elements; i++) {
        fprintf(file, "%d\n", rand());
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Használat: %s <fájl neve> <elemszám>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int num_elements = atoi(argv[2]);

    if (num_elements <= 0) {
        printf("Hiba: Az elemszámnak pozitív egész számnak kell lennie.\n");
        return 1;
    }

    srand(time(NULL));

    clock_t start_generate = clock(); 
    generate_random_numbers(filename, num_elements);
    clock_t end_generate = clock();

    double generate_time = (double)(end_generate - start_generate) / CLOCKS_PER_SEC;
    
    printf("Fájl: %s, Elemszám: %d\n", filename, num_elements);
    printf("Véletlenszámok generálásának ideje: %f másodperc\n", generate_time);

    return 0;
}
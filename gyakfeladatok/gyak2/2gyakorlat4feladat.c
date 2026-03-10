#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Függvények deklarálása
void generate_random_text(char *filename, int num_chars);
void count_lines_and_empty_lines(char *filename, int *line_count, int *empty_line_count);
void count_lines_and_empty_lines_recursive(FILE *file, int *line_count, int *empty_line_count);
void print_execution_time(clock_t start, clock_t end, const char *message);
char random_char(void);

int main() {
    int num_chars;
    char filename[] = "random_text.txt";

    // A fájl generálásához szükséges karakterek számának beolvasása
    printf("Adja meg a generálandó karakterek számát: ");
    scanf("%d", &num_chars);

    // A szöveg generálása
    clock_t start, end;
    start = clock();
    generate_random_text(filename, num_chars);
    end = clock();
    print_execution_time(start, end, "Szöveg fájlba írásának ideje");

    // Iteratív módszerrel a sorok és üres sorok számolása
    int line_count = 0, empty_line_count = 0;
    start = clock();
    count_lines_and_empty_lines(filename, &line_count, &empty_line_count);
    end = clock();
    print_execution_time(start, end, "Sorok és üres sorok számolásának ideje (iteratív)");

    printf("Fájlban lévő sorok száma: %d\n", line_count);
    printf("Üres sorok száma: %d\n", empty_line_count);

    // Rekurzív módszerrel a sorok és üres sorok számolása
    FILE *file = fopen(filename, "r");
    line_count = 0;
    empty_line_count = 0;
    start = clock();
    count_lines_and_empty_lines_recursive(file, &line_count, &empty_line_count);
    end = clock();
    print_execution_time(start, end, "Sorok és üres sorok számolásának ideje (rekurzív)");

    printf("Fájlban lévő sorok száma: %d\n", line_count);
    printf("Üres sorok száma: %d\n", empty_line_count);

    // Fájl bezárása
    fclose(file);

    return 0;
}

// Véletlenszerű szöveg generálása
void generate_random_text(char *filename, int num_chars) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Nem sikerült fájlt nyitni!\n");
        return;
    }

    for (int i = 0; i < num_chars; i++) {
        // Véletlenszerű karakterek generálása
        char c = random_char();

        // Véletlenszerű sortörés (kb. 10%-os valószínűséggel)
        if (rand() % 10 == 0) {
            fprintf(file, "\n");
        } else {
            fprintf(file, "%c", c);
        }
    }

    fclose(file);
}

// Véletlenszerű karakterek generálása (kis és nagybetűk, számjegyek, szóköz)
char random_char(void) {
    int rand_val = rand() % 4;
    switch (rand_val) {
        case 0: return 'a' + rand() % ALPHABET_SIZE;  // Kisbetű
        case 1: return 'A' + rand() % ALPHABET_SIZE;  // Nagybetű
        case 2: return '0' + rand() % 10;            // Számjegy
        case 3: return ' ';                          // Szóköz
        default: return ' ';  // Alapértelmezett: szóköz
    }
}

// Iteratív módon megszámolja a sorokat és az üres sorokat
void count_lines_and_empty_lines(char *filename, int *line_count, int *empty_line_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nem sikerült fájlt megnyitni!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*line_count)++;
            char next_ch = fgetc(file);
            if (next_ch == '\n' || next_ch == EOF) {
                (*empty_line_count)++;
            }
            ungetc(next_ch, file);  // Visszateszi a következő karaktert a fájlba
        }
    }

    fclose(file);
}

// Rekurzív módon megszámolja a sorokat és az üres sorokat
void count_lines_and_empty_lines_recursive(FILE *file, int *line_count, int *empty_line_count) {
    char ch = fgetc(file);
    if (ch == EOF) {
        return;
    }

    if (ch == '\n') {
        (*line_count)++;
        char next_ch = fgetc(file);
        if (next_ch == '\n' || next_ch == EOF) {
            (*empty_line_count)++;
        }
        ungetc(next_ch, file);  // Visszateszi a következő karaktert a fájlba
    }

    count_lines_and_empty_lines_recursive(file, line_count, empty_line_count);  // Rekurzív hívás
}

// Futási idő kiírása
void print_execution_time(clock_t start, clock_t end, const char *message) {
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s: %f másodperc\n", message, time_taken);
}
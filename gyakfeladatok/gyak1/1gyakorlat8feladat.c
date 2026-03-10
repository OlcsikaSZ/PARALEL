#include <stdio.h>
#include <stdlib.h>

void write_int_to_file(const char *filename, int *arr, int size);
void write_long_to_file(const char *filename, long *arr, int size);
void write_float_to_file(const char *filename, float *arr, int size);

void read_int_from_file(const char *filename, int *arr, int size);
void read_long_from_file(const char *filename, long *arr, int size);
void read_float_from_file(const char *filename, float *arr, int size);

long get_file_size(const char *filename);

int main() {
    int int_arr[] = {1, 2, 3, 4, 5};
    long long_arr[] = {100000, 200000, 300000, 400000, 500000};
    float float_arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};

    const char *int_filename = "int_data.txt";
    const char *long_filename = "long_data.txt";
    const char *float_filename = "float_data.txt";

    write_int_to_file(int_filename, int_arr, 5);
    write_long_to_file(long_filename, long_arr, 5);
    write_float_to_file(float_filename, float_arr, 5);

    printf("File size of %s: %ld bytes\n", int_filename, get_file_size(int_filename));
    printf("File size of %s: %ld bytes\n", long_filename, get_file_size(long_filename));
    printf("File size of %s: %ld bytes\n", float_filename, get_file_size(float_filename));

    int read_int_arr[5];
    long read_long_arr[5];
    float read_float_arr[5];

    read_int_from_file(int_filename, read_int_arr, 5);
    read_long_from_file(long_filename, read_long_arr, 5);
    read_float_from_file(float_filename, read_float_arr, 5);

    printf("Read int values from file:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", read_int_arr[i]);
    }
    printf("\n");

    printf("Read long values from file:\n");
    for (int i = 0; i < 5; i++) {
        printf("%ld ", read_long_arr[i]);
    }
    printf("\n");

    printf("Read float values from file:\n");
    for (int i = 0; i < 5; i++) {
        printf("%.2f ", read_float_arr[i]);
    }
    printf("\n");

    return 0;
}

void write_int_to_file(const char *filename, int *arr, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }
    fwrite(arr, sizeof(int), size, file);
    fclose(file);
}

void write_long_to_file(const char *filename, long *arr, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }
    fwrite(arr, sizeof(long), size, file);
    fclose(file);
}

void write_float_to_file(const char *filename, float *arr, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }
    fwrite(arr, sizeof(float), size, file);
    fclose(file);
}

void read_int_from_file(const char *filename, int *arr, int size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }
    fread(arr, sizeof(int), size, file);
    fclose(file);
}

void read_long_from_file(const char *filename, long *arr, int size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }
    fread(arr, sizeof(long), size, file);
    fclose(file);
}

void read_float_from_file(const char *filename, float *arr, int size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }
    fread(arr, sizeof(float), size, file);
    fclose(file);
}

long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Fájl megnyitási hiba");
        exit(1);
    }

    fseek(file, 0, SEEK_END); 
    long size = ftell(file); 
    fclose(file);

    return size;
}
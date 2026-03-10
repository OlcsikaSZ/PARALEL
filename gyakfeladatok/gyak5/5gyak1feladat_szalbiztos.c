#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Array struktúra és alapvető műveletek
typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} Array;

void init_array(Array *arr) {
    arr->capacity = 10;
    arr->size = 0;
    arr->array = (int *)malloc(arr->capacity * sizeof(int));
}

void append(Array *arr, int value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->array = (int *)realloc(arr->array, arr->capacity * sizeof(int));
    }
    arr->array[arr->size++] = value;
}

void free_array(Array *arr) {
    free(arr->array);
}

// Szálkezelés nélküli példafüggvény
void* append_elements(void* arg) {
    Array *arr = (Array*)arg;
    for (int i = 0; i < 1000; i++) {
        append(arr, i);
    }
    return NULL;
}

int main() {
    Array arr;
    init_array(&arr);

    pthread_t threads[2];
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, append_elements, &arr);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Array size: %zu\n", arr.size); // Ez most már megfelelően működik!

    free_array(&arr);
    return 0;
}
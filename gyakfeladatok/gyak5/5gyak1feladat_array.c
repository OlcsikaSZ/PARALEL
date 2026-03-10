#include <stdio.h>
#include <stdlib.h>

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

void resize_array(Array *arr) {
    arr->capacity *= 2;
    arr->array = (int *)realloc(arr->array, arr->capacity * sizeof(int));
}

void append(Array *arr, int value) {
    if (arr->size >= arr->capacity) {
        resize_array(arr);
    }
    arr->array[arr->size++] = value;
}

void remove_at(Array *arr, size_t index) {
    if (index >= arr->size) return;
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->array[i] = arr->array[i + 1];
    }
    arr->size--;
}

int get(Array *arr, size_t index) {
    if (index >= arr->size) return -1; // Hiba: érvénytelen index
    return arr->array[index];
}

void free_array(Array *arr) {
    free(arr->array);
}

int main() {
    Array arr;
    init_array(&arr);
    
    for (int i = 0; i < 20; i++) {
        append(&arr, i);
    }
    
    for (size_t i = 0; i < arr.size; i++) {
        printf("%d ", get(&arr, i));
    }
    
    free_array(&arr);
    return 0;
}
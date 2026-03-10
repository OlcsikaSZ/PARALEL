#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int *array;
    int top;
    int capacity;
} Stack;

void init_stack(Stack *s, int capacity) {
    s->capacity = capacity;
    s->top = -1;
    s->array = (int *)malloc(s->capacity * sizeof(int));
}

int is_empty_stack(Stack *s) {
    return s->top == -1;
}

int is_full_stack(Stack *s) {
    return s->top == s->capacity - 1;
}

void push(Stack *s, int value) {
    if (is_full_stack(s)) return;
    s->array[++s->top] = value;
}

int pop(Stack *s) {
    if (is_empty_stack(s)) return -1;
    return s->array[s->top--];
}

void free_stack(Stack *s) {
    free(s->array);
}

int main() {
    Stack s;
    init_stack(&s, 10);
    
    for (int i = 0; i < 5; i++) {
        push(&s, i);
    }
    
    while (!is_empty_stack(&s)) {
        printf("%d ", pop(&s));
    }
    
    free_stack(&s);
    return 0;
}
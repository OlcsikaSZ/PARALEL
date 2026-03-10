#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int *array;
    int front;
    int rear;
    int capacity;
} Queue;

void init_queue(Queue *q, int capacity) {
    q->capacity = capacity;
    q->front = q->rear = -1;
    q->array = (int *)malloc(q->capacity * sizeof(int));
}

int is_empty(Queue *q) {
    return q->front == -1;
}

int is_full(Queue *q) {
    return q->rear == q->capacity - 1;
}

void enqueue(Queue *q, int value) {
    if (is_full(q)) return;
    if (q->front == -1) q->front = 0;
    q->array[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (is_empty(q)) return -1;
    int value = q->array[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

void free_queue(Queue *q) {
    free(q->array);
}

int main() {
    Queue q;
    init_queue(&q, 10);
    
    for (int i = 0; i < 5; i++) {
        enqueue(&q, i);
    }
    
    while (!is_empty(&q)) {
        printf("%d ", dequeue(&q));
    }
    
    free_queue(&q);
    return 0;
}
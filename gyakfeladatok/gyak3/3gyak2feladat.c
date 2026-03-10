#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 60

// Szál függvénye, amely 1 másodpercig számít
void* thread_function(void* arg) {
    sleep(1);  // 1 másodpercig "számít"
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Elindítjuk 60 szálat
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    // Megvárjuk mindegyik szál befejezését
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");

    return 0;
}
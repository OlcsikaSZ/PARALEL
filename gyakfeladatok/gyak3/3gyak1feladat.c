#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// A második szál függvénye (4 másodpercig számít)
void* thread_function_2(void* arg) {
    printf("Thread 2 starts...\n");
    sleep(4);  // 4 másodpercig alszik, így szimulálva a számítást
    printf("Thread 2 finishes after 4 seconds.\n");
    return NULL;
}

// A fő szál függvénye (8 másodpercig számít)
void* thread_function_1(void* arg) {
    pthread_t thread2;
    printf("Main thread starts...\n");

    // Elindítjuk a második szálat
    pthread_create(&thread2, NULL, thread_function_2, NULL);
    
    // A fő szál 8 másodpercig számít
    sleep(8);
    printf("Main thread finishes after 8 seconds.\n");

    // Megvárjuk a második szál befejezését
    pthread_join(thread2, NULL);
    return NULL;
}

int main() {
    pthread_t thread1;

    // Elindítjuk az első szálat (fő szál)
    pthread_create(&thread1, NULL, thread_function_1, NULL);

    // Megvárjuk az első szál befejezését
    pthread_join(thread1, NULL);

    return 0;
}
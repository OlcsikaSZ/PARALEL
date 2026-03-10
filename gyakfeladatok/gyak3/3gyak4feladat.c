#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);

    if (thread_id == 3) {  // Simuláljuk egy szál hibáját
        printf("Thread %d encountered an error!\n", thread_id);
        return (void*)-1;  // Hibás visszatérés
    }

    sleep(1);  // Normális futás
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5];

    // Elindítjuk a szálakat
    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Megvárjuk a szálakat, és ellenőrizzük a visszatérési értékeket
    for (int i = 0; i < 5; i++) {
        void* result;
        pthread_join(threads[i], &result);
        if (result == (void*)-1) {
            printf("Thread %d failed.\n", i);
        } else {
            printf("Thread %d finished successfully.\n", i);
        }
    }

    return 0;
}
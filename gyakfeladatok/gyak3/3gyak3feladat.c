#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_THREADS 10
#define INTERVAL_SIZE 100

int prime_counts[NUM_THREADS] = {0};

// Prímszám ellenőrző függvény
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Szál függvénye, amely a megadott intervallumban számolja a prímszámokat
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    int start = thread_id * INTERVAL_SIZE;
    int end = start + INTERVAL_SIZE;

    int count = 0;
    for (int i = start; i < end; i++) {
        if (is_prime(i)) {
            count++;
        }
    }

    prime_counts[thread_id] = count;
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Elindítjuk a szálakat
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Megvárjuk mindegyik szál befejezését
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Kiírjuk a prímszámokat számoló szálak eredményeit
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Thread %d found %d primes in interval [%d, %d)\n", i, prime_counts[i], i * INTERVAL_SIZE, (i + 1) * INTERVAL_SIZE);
    }

    return 0;
}
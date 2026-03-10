#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) { 
        if (num % i == 0) return false;
    }
    return true;
}

int count_primes(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int n_values[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 
                      11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        

        clock_t start = clock();

        int prime_count = count_primes(n);
        
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // Másodpercekben

        printf("n = %d, Prímszámok száma: %d, Futási idő: %f másodperc\n", n, prime_count, time_spent);
    }

    return 0;
}
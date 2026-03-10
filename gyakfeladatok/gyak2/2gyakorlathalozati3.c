#include <stdio.h>
#include <math.h>

// Csomópontok számítása n-dimenziós hiperkocka esetén
int calculate_nodes(int n) {
    return (int)pow(2, n);  // 2^n
}

// Élek számítása n-dimenziós hiperkocka esetén
int calculate_edges(int n) {
    return n * (int)pow(2, n - 1);  // n * 2^(n-1)
}

// Hamming-távolság kiszámítása két bináris szám között
int hamming_distance(int a, int b, int n) {
    int diff = a ^ b;  // XOR az eltéréseket mutatja
    int dist = 0;
    for (int i = 0; i < n; i++) {
        dist += (diff >> i) & 1;  // Számolja, hány 1-es bit van
    }
    return dist;
}

// Távolságok eloszlása 8 dimenziós hiperkocka esetén
void calculate_8d_distances(int n) {
    int nodes = (int)pow(2, n);
    printf("8D hiperkocka távolságok:\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = i + 1; j < nodes; j++) {
            int dist = hamming_distance(i, j, n);
            printf("Csomópontok: %d, %d - Távolság: %d\n", i, j, dist);
        }
    }
}

// Átlagos távolságok számítása n dimenziós hiperkocka esetén
float calculate_avg_distance(int n) {
    int nodes = (int)pow(2, n);
    int total_distance = 0;
    int total_pairs = 0;
    for (int i = 0; i < nodes; i++) {
        for (int j = i + 1; j < nodes; j++) {
            total_distance += hamming_distance(i, j, n);
            total_pairs++;
        }
    }
    return (float)total_distance / total_pairs;
}

int main() {
    // 30 dimenzióig csomópontok és élek száma
    printf("Hiperkocka csomópontok és élek száma (30 dimenzióig):\n");
    for (int n = 1; n <= 30; n++) {
        int nodes = calculate_nodes(n);
        int edges = calculate_edges(n);
        printf("n = %d: Csomópontok = %d, Élek = %d\n", n, nodes, edges);
    }

    // 8 dimenzió esetén távolságok eloszlása
    printf("\n8 dimenziós hiperkocka távolságok:\n");
    calculate_8d_distances(8);

    // Átlagos távolságok számítása 20 dimenzióig
    printf("\nÁtlagos távolságok (20 dimenzióig):\n");
    for (int n = 1; n <= 20; n++) {
        float avg_dist = calculate_avg_distance(n);
        printf("n = %d: Átlagos távolság = %.4f\n", n, avg_dist);
    }

    return 0;
}
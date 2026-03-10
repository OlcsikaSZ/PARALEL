#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_N 50
#define SIZE_2D 12
#define SIZE_3D 5

// 2D rács csomópontok és élek számítása
void calculate_2d(int n) {
    int num_nodes = n * n;
    int num_edges = 2 * n * (n - 1);
    printf("n = %d: Csomópontok = %d, Élek = %d, Arány = %.4f\n",
           n, num_nodes, num_edges, (float)num_edges / num_nodes);
}

// Távolságok eloszlása 2D rácsban
void calculate_2d_distances(int size) {
    float distances[(size-1)*(size-1)];
    int index = 0;
    
    for (int x1 = 0; x1 < size; x1++) {
        for (int y1 = 0; y1 < size; y1++) {
            for (int x2 = x1 + 1; x2 < size; x2++) {
                for (int y2 = y1 + 1; y2 < size; y2++) {
                    float dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
                    distances[index++] = dist;
                }
            }
        }
    }

    // Hisztogram kiírása
    printf("Távolságok eloszlása a %dx%d-es rácsban:\n", size, size);
    for (int i = 0; i < index; i++) {
        printf("%.2f ", distances[i]);
    }
    printf("\n");
}

// Térbeli rács csomópontok és élek számítása
void calculate_3d(int n) {
    int num_nodes = n * n * n;
    int num_edges = 3 * n * n * (n - 1);
    printf("n = %d: Térbeli csomópontok = %d, Élek = %d, Arány = %.4f\n",
           n, num_nodes, num_edges, (float)num_edges / num_nodes);
}

// Távolságok eloszlása 3D rácsban
void calculate_3d_distances(int size) {
    float distances[size * size * size * size * size * size];
    int index = 0;
    
    for (int x1 = 0; x1 < size; x1++) {
        for (int y1 = 0; y1 < size; y1++) {
            for (int z1 = 0; z1 < size; z1++) {
                for (int x2 = x1 + 1; x2 < size; x2++) {
                    for (int y2 = y1 + 1; y2 < size; y2++) {
                        for (int z2 = z1 + 1; z2 < size; z2++) {
                            float dist = sqrt((x2 - x1) * (x2 - x1) + 
                                              (y2 - y1) * (y2 - y1) + 
                                              (z2 - z1) * (z2 - z1));
                            distances[index++] = dist;
                        }
                    }
                }
            }
        }
    }

    // Hisztogram kiírása
    printf("Távolságok eloszlása a %dx%dx%d-es rácsban:\n", size, size, size);
    for (int i = 0; i < index; i++) {
        printf("%.2f ", distances[i]);
    }
    printf("\n");
}

int main() {
    // 2D rács számítások
    printf("2D rács:\n");
    for (int n = 1; n <= MAX_N; n++) {
        calculate_2d(n);
    }

    // 2D rács távolságok
    calculate_2d_distances(SIZE_2D);

    // Térbeli rács számítások
    printf("\nTérbeli rács:\n");
    for (int n = 1; n <= 24; n++) {
        calculate_3d(n);
    }

    // 3D rács távolságok
    calculate_3d_distances(SIZE_3D);

    return 0;
}
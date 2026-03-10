#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 2D Tórusz rács csomópontok és élek számítása
void calculate_2d_torus(int n) {
    int num_nodes = n * n;
    int num_edges = 4 * n * n;  // A tórusz esetén 4n^2 él van
    printf("Tórusz 2D n = %d: Csomópontok = %d, Élek = %d, Arány = %.4f\n",
           n, num_nodes, num_edges, (float)num_edges / num_nodes);
}

// Távolságok eloszlása 2D tórusz rácsban
void calculate_2d_torus_distances(int size) {
    float distances[(size-1)*(size-1)];
    int index = 0;

    for (int x1 = 0; x1 < size; x1++) {
        for (int y1 = 0; y1 < size; y1++) {
            for (int x2 = x1 + 1; x2 < size; x2++) {
                for (int y2 = y1 + 1; y2 < size; y2++) {
                    int dx = abs(x2 - x1);
                    int dy = abs(y2 - y1);
                    dx = (dx > size / 2) ? size - dx : dx;  // Wrap-around hatás
                    dy = (dy > size / 2) ? size - dy : dy;  // Wrap-around hatás
                    float dist = sqrt(dx * dx + dy * dy);
                    distances[index++] = dist;
                }
            }
        }
    }

    // Hisztogram kiírása
    printf("Távolságok eloszlása a %dx%d-es tórusz rácsban:\n", size, size);
    for (int i = 0; i < index; i++) {
        printf("%.2f ", distances[i]);
    }
    printf("\n");
}

// 3D Tórusz rács csomópontok és élek számítása
void calculate_3d_torus(int n) {
    int num_nodes = n * n * n;
    int num_edges = 6 * n * n * (n - 1);  // Térbeli tórusz esetén 6n^2(n-1) él van
    printf("Tórusz 3D n = %d: Csomópontok = %d, Élek = %d, Arány = %.4f\n",
           n, num_nodes, num_edges, (float)num_edges / num_nodes);
}

// Távolságok eloszlása 3D tórusz rácsban
void calculate_3d_torus_distances(int size) {
    float distances[size * size * size * size * size * size];
    int index = 0;

    for (int x1 = 0; x1 < size; x1++) {
        for (int y1 = 0; y1 < size; y1++) {
            for (int z1 = 0; z1 < size; z1++) {
                for (int x2 = x1 + 1; x2 < size; x2++) {
                    for (int y2 = y1 + 1; y2 < size; y2++) {
                        for (int z2 = z1 + 1; z2 < size; z2++) {
                            int dx = abs(x2 - x1);
                            int dy = abs(y2 - y1);
                            int dz = abs(z2 - z1);
                            dx = (dx > size / 2) ? size - dx : dx;  // Wrap-around hatás
                            dy = (dy > size / 2) ? size - dy : dy;  // Wrap-around hatás
                            dz = (dz > size / 2) ? size - dz : dz;  // Wrap-around hatás
                            float dist = sqrt(dx * dx + dy * dy + dz * dz);
                            distances[index++] = dist;
                        }
                    }
                }
            }
        }
    }

    // Hisztogram kiírása
    printf("Távolságok eloszlása a %dx%dx%d-es tórusz rácsban:\n", size, size, size);
    for (int i = 0; i < index; i++) {
        printf("%.2f ", distances[i]);
    }
    printf("\n");
}

int main() {
    // 2D tórusz rács számítások
    printf("2D tórusz rács:\n");
    for (int n = 1; n <= 50; n++) {
        calculate_2d_torus(n);
    }

    // 2D tórusz távolságok
    calculate_2d_torus_distances(12);

    // 3D tórusz rács számítások
    printf("\n3D tórusz rács:\n");
    for (int n = 1; n <= 24; n++) {
        calculate_3d_torus(n);
    }

    // 3D tórusz távolságok
    calculate_3d_torus_distances(5);

    return 0;
}
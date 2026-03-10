#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Mátrix létrehozása és inicializálása
int** create_matrix(int n) {
    int **matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Mátrix felszabadítása
void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Egység mátrix ellenőrzése
int is_identity(int **matrix, int n) {
    int is_identity = 1;
    #pragma omp parallel for shared(is_identity)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == j && matrix[i][j] != 1) || (i != j && matrix[i][j] != 0)) {
                is_identity = 0;
            }
        }
    }
    return is_identity;
}

// Diagonális mátrix ellenőrzése
int is_diagonal(int **matrix, int n) {
    int is_diagonal = 1;
    #pragma omp parallel for shared(is_diagonal)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrix[i][j] != 0) {
                is_diagonal = 0;
            }
        }
    }
    return is_diagonal;
}

// Szimmetrikus mátrix ellenőrzése
int is_symmetric(int **matrix, int n) {
    int is_symmetric = 1;
    #pragma omp parallel for shared(is_symmetric)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                is_symmetric = 0;
            }
        }
    }
    return is_symmetric;
}

// Normák számítása

// 1-es norma (oszlopösszeg maximum)
double norm_1(int **matrix, int n) {
    double max_sum = 0.0;
    #pragma omp parallel for reduction(max:max_sum)
    for (int j = 0; j < n; j++) {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += fabs(matrix[i][j]);
        }
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

// 2-es norma (Frobenius norma)
double norm_2(int **matrix, int n) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j] * matrix[i][j];
        }
    }
    return sqrt(sum);
}

// Végtelen norma (sorösszeg maximum)
double norm_inf(int **matrix, int n) {
    double max_sum = 0.0;
    #pragma omp parallel for reduction(max:max_sum)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += fabs(matrix[i][j]);
        }
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

// Mátrix tulajdonság ellenőrzése egyéni függvénnyel
int check_property(int value, int row, int col) {
    // Példa: Elem páros, és az indexek összege is páros
    return (value % 2 == 0) && ((row + col) % 2 == 0);
}

// Mátrix kiíratása
void print_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; // Mátrix mérete
    int **matrix = create_matrix(n);

    // Mátrix véletlenszerű feltöltése
    srand(0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 2;  // 0 vagy 1 értékek
        }
    }

    printf("Mátrix:\n");
    print_matrix(matrix, n);

    // Egység mátrix ellenőrzése
    if (is_identity(matrix, n)) {
        printf("A mátrix egység mátrix.\n");
    } else {
        printf("A mátrix nem egység mátrix.\n");
    }

    // Diagonális mátrix ellenőrzése
    if (is_diagonal(matrix, n)) {
        printf("A mátrix diagonális.\n");
    } else {
        printf("A mátrix nem diagonális.\n");
    }

    // Szimmetrikus mátrix ellenőrzése
    if (is_symmetric(matrix, n)) {
        printf("A mátrix szimmetrikus.\n");
    } else {
        printf("A mátrix nem szimmetrikus.\n");
    }

    // Normák számítása
    double norm1 = norm_1(matrix, n);
    printf("1-es norma: %f\n", norm1);

    double norm2 = norm_2(matrix, n);
    printf("2-es norma: %f\n", norm2);

    double norm_inf_val = norm_inf(matrix, n);
    printf("Végtelen norma: %f\n", norm_inf_val);

    // Tulajdonság ellenőrzése minden elemre
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (check_property(matrix[i][j], i, j)) {
                printf("Elem (%d, %d) megfelel a tulajdonságnak.\n", i, j);
            }
        }
    }

    free_matrix(matrix, n);
    return 0;
}
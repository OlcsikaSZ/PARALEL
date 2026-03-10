#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>  // usleep()

#define ROWS 1000
#define COLS 1000
#define ITERATIONS 1000
#define NUM_THREADS 10
#define DISPLAY_ROWS 50
#define DISPLAY_COLS 50

int grid[ROWS][COLS];
int new_grid[ROWS][COLS];
int display_enabled = 1;

void initialize_grid() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

int count_neighbors(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void display_grid() {
    for (int i = 0; i < DISPLAY_ROWS && i < ROWS; i++) {
        for (int j = 0; j < DISPLAY_COLS && j < COLS; j++) {
            printf("%c", grid[i][j] ? '#' : ' ');
        }
        printf("\n");
    }
    fflush(stdout);
    usleep(500000);
}

void update_grid() {
    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = count_neighbors(i, j);
            new_grid[i][j] = (grid[i][j] == 1 && (neighbors == 2 || neighbors == 3)) ||
                             (grid[i][j] == 0 && neighbors == 3);
        }
    }

    #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

int main() {
    printf("Megjelenítés engedélyezése? (1=igen, 0=nem): ");
    scanf("%d", &display_enabled);

    srand(time(NULL));
    initialize_grid();

    double start_time = omp_get_wtime();

    for (int iter = 0; iter < ITERATIONS; iter++) {
        update_grid();
        if (display_enabled) {
            printf("Iteráció: %d\n", iter + 1);
            display_grid();
        }
    }

    double end_time = omp_get_wtime();

    printf("\nFutásidő: %.6f másodperc\n", end_time - start_time);
    printf("Grid méret: %dx%d\n", ROWS, COLS);
    printf("Iterációk száma: %d\n", ITERATIONS);
    printf("Szálak száma: %d\n", NUM_THREADS);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define ROWS 2000
#define COLS 2000
#define ITERATIONS 1000
#define NUM_THREADS 10
#define DISPLAY_ROWS 50
#define DISPLAY_COLS 50

int grid[ROWS][COLS];
int new_grid[ROWS][COLS];
int display_enabled = 1;
pthread_barrier_t barrier;

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
    usleep(500000);  // Kis szünet, hogy ne villogjon túl gyorsan
}

void *update_grid(void *arg) {
    int thread_id = *(int *)arg;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        // 1. fázis: új állapot kiszámítása
        for (int i = thread_id; i < ROWS; i += NUM_THREADS) {
            for (int j = 0; j < COLS; j++) {
                int neighbors = count_neighbors(i, j);
                new_grid[i][j] = (grid[i][j] == 1 && (neighbors == 2 || neighbors == 3)) ||
                                 (grid[i][j] == 0 && neighbors == 3);
            }
        }

        pthread_barrier_wait(&barrier);

        // 2. fázis: új állapot átmásolása
        for (int i = thread_id; i < ROWS; i += NUM_THREADS) {
            for (int j = 0; j < COLS; j++) {
                grid[i][j] = new_grid[i][j];
            }
        }

        pthread_barrier_wait(&barrier);

        // Csak az első szál jeleníti meg
        if (display_enabled && thread_id == 0) {
            printf("Iteráció: %d\n", iter + 1);
            display_grid();
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Megjelenítés engedélyezése? (1=igen, 0=nem): ");
    scanf("%d", &display_enabled);

    srand(time(NULL));
    initialize_grid();
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    clock_t start = clock();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, update_grid, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    pthread_barrier_destroy(&barrier);

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nFutásidő: %.6f másodperc\n", elapsed_time);
    printf("Grid méret: %dx%d\n", ROWS, COLS);
    printf("Iterációk száma: %d\n", ITERATIONS);
    printf("Szálak száma: %d\n", NUM_THREADS);

    return 0;
}
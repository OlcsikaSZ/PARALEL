#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // usleep()

#define ROWS 50
#define COLS 50
#define ITERATIONS 100

#define DISPLAY_ROWS 50
#define DISPLAY_COLS 50
#define DISPLAY_DELAY_US 500000

int grid[ROWS][COLS];
int new_grid[ROWS][COLS];

int enable_display = 0;

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

void update_grid() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = count_neighbors(i, j);
            new_grid[i][j] = (grid[i][j] == 1 && (neighbors == 2 || neighbors == 3)) ||
                             (grid[i][j] == 0 && neighbors == 3);
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

void display_grid(int iter) {
    //system("cls"); 
    printf("Iteráció: %d\n", iter);
    for (int i = 0; i < DISPLAY_ROWS && i < ROWS; i++) {
        for (int j = 0; j < DISPLAY_COLS && j < COLS; j++) {
            putchar(grid[i][j] ? '#' : ' ');
        }
        putchar('\n');
    }
    usleep(500000);
}

int main() {
    srand(time(NULL));
    char choice;
    
    printf("Szeretnéd látni a kirajzolt iterációkat? (1=igen, 0=nem): ");
    scanf(" %c", &choice);
    if (choice == '1' || choice == '1') {
        enable_display = 1;
    }

    initialize_grid();
    clock_t start = clock();

    for (int iter = 0; iter < ITERATIONS; iter++) {
        update_grid();
        if (enable_display) {
            display_grid(iter);
        }
    }

    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nFutásidő: %.6f másodperc\n", elapsed_time);
    printf("Grid méret: %dx%d\n", ROWS, COLS);
    printf("Iterációk száma: %d\n", ITERATIONS);

    return 0;
}
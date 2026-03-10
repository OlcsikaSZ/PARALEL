%%writefile game_of_life.cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <time.h>

#define ROWS 1000
#define COLS 1000
#define ITERATIONS 1000
#define BLOCK_SIZE 1

#define CUDA_CHECK(ans) { gpuAssert((ans), __FILE__, __LINE__); }

inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true) {
   if (code != cudaSuccess) {
      fprintf(stderr, "CUDA Error: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

__global__ void update_grid(int *grid, int *new_grid, int rows, int cols) {
    // A szál koordinátái a teljes gridben
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    // A szál koordinátái a shared memory blokkon belül (plusz halo)
    int tx = threadIdx.x + 1;
    int ty = threadIdx.y + 1;

    // Shared memory blokk (BLOCK_SIZE + 2)^2 (halo-val együtt)
    __shared__ int local[BLOCK_SIZE + 2][BLOCK_SIZE + 2];

    // Beolvasás shared memóriába
    if (x < rows && y < cols) {
        local[tx][ty] = grid[x * cols + y];

        // Szomszédos cellák (halo) beolvasása
        if (threadIdx.x == 0 && x > 0)
            local[tx - 1][ty] = grid[(x - 1) * cols + y];
        if (threadIdx.x == blockDim.x - 1 && x < rows - 1)
            local[tx + 1][ty] = grid[(x + 1) * cols + y];
        if (threadIdx.y == 0 && y > 0)
            local[tx][ty - 1] = grid[x * cols + (y - 1)];
        if (threadIdx.y == blockDim.y - 1 && y < cols - 1)
            local[tx][ty + 1] = grid[x * cols + (y + 1)];

        // Sarki halo elemek
        if (threadIdx.x == 0 && threadIdx.y == 0 && x > 0 && y > 0)
            local[tx - 1][ty - 1] = grid[(x - 1) * cols + (y - 1)];
        if (threadIdx.x == 0 && threadIdx.y == blockDim.y - 1 && x > 0 && y < cols - 1)
            local[tx - 1][ty + 1] = grid[(x - 1) * cols + (y + 1)];
        if (threadIdx.x == blockDim.x - 1 && threadIdx.y == 0 && x < rows - 1 && y > 0)
            local[tx + 1][ty - 1] = grid[(x + 1) * cols + (y - 1)];
        if (threadIdx.x == blockDim.x - 1 && threadIdx.y == blockDim.y - 1 && x < rows - 1 && y < cols - 1)
            local[tx + 1][ty + 1] = grid[(x + 1) * cols + (y + 1)];
    }

    __syncthreads(); // Várjuk meg, míg mindenki beolvasott

    if (x < rows && y < cols) {
        int count = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                count += local[tx + dx][ty + dy];
            }
        }
        count -= local[tx][ty];

        new_grid[x * cols + y] = (local[tx][ty] == 1 && (count == 2 || count == 3)) ||
                                 (local[tx][ty] == 0 && count == 3);
    }
}

void initialize_grid(int *grid, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        grid[i] = rand() % 2;
    }
}

int main() {
    int *grid, *new_grid;
    int *d_grid, *d_new_grid;
    size_t size = ROWS * COLS * sizeof(int);

    cudaMallocHost(&grid, size);
    cudaMallocHost(&new_grid, size);
    cudaMalloc(&d_grid, size);
    cudaMalloc(&d_new_grid, size);

    initialize_grid(grid, ROWS, COLS);
    cudaMemcpy(d_grid, grid, size, cudaMemcpyHostToDevice);

    dim3 blockSize(BLOCK_SIZE, BLOCK_SIZE);
    dim3 gridSize((ROWS + BLOCK_SIZE - 1) / BLOCK_SIZE, (COLS + BLOCK_SIZE - 1) / BLOCK_SIZE);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Eltávolítva: kezdő állapot kirajzolása
    // printf("Kezdő állapot:\n");
    // print_sample(grid, ROWS, COLS);

    cudaMemcpy(d_grid, grid, size, cudaMemcpyHostToDevice);

    // Start timing
    cudaEventRecord(start);
    for (int i = 0; i < ITERATIONS; i++) {
        update_grid<<<gridSize, blockSize>>>(d_grid, d_new_grid, ROWS, COLS);

        int *tmp = d_grid;
        d_grid = d_new_grid;
        d_new_grid = tmp;
    }
    // Only one sync at the end!
    cudaEventRecord(stop);

    CUDA_CHECK(cudaMallocHost(&grid, size));
    CUDA_CHECK(cudaMalloc(&d_grid, size));
    CUDA_CHECK(cudaMemcpy(d_grid, grid, size, cudaMemcpyHostToDevice));

    update_grid<<<gridSize, blockSize>>>(d_grid, d_new_grid, ROWS, COLS);
    CUDA_CHECK(cudaGetLastError());  // Kernel indítás hibájának ellenőrzése
    CUDA_CHECK(cudaDeviceSynchronize());  // Kernel futásának befejezése és hibaellenőrzése
    cudaDeviceSynchronize();

    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    printf("\nFutásidő: %.6f másodperc\n", milliseconds / 1000.0);
    printf("Grid méret: %dx%d\n", ROWS, COLS);
    printf("Iterációk száma: %d\n", ITERATIONS);
    printf("Blokk méret: %dx%d\n", BLOCK_SIZE, BLOCK_SIZE);

    // Eltávolítva: végső állapot kirajzolása
    // printf("\nVégső állapot:\n");
    // print_sample(grid, ROWS, COLS);

    cudaFree(d_grid);
    cudaFree(d_new_grid);
    cudaFreeHost(grid);
    cudaFreeHost(new_grid);
    return 0;
}

!nvcc -arch=sm_70 -o game_of_life game_of_life.cu
!./game_of_life
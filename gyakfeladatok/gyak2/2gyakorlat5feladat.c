#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crew_prefix(int *arr, int *out, int start, int end, FILE *graph_file, int *counter);
void print_graph(FILE *graph_file, int *counter, int start, int end);

int main() {
    int n;
    printf("Adja meg a bemeneti tömb méretét (n): ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    int *out = (int *)malloc(n * sizeof(int));

    // Véletlenszerű értékek generálása a bemeneti tömbhöz
    printf("Bemeneti tömb elemei: ");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10;  // Random számok [0-9]
        printf("%d ", arr[i]);
    }
    printf("\n");

    // A GraphViz fájl megnyitása
    FILE *graph_file = fopen("crew_prefix_calls.dot", "w");
    if (graph_file == NULL) {
        printf("Nem sikerült fájlt megnyitni!\n");
        return -1;
    }

    // GraphViz fájl fejléce
    fprintf(graph_file, "digraph G {\n");
    fprintf(graph_file, "node [shape=rectangle];\n");

    // Hívások elvégzése
    int counter = 0;
    crew_prefix(arr, out, 0, n - 1, graph_file, &counter);

    // GraphViz fájl lezárása
    fprintf(graph_file, "}\n");
    fclose(graph_file);

    // Eredmény kiírása
    printf("Az eredmény tömb: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", out[i]);
    }
    printf("\n");

    free(arr);
    free(out);
    return 0;
}

// CREW_PREFIX algoritmus
void crew_prefix(int *arr, int *out, int start, int end, FILE *graph_file, int *counter) {
    if (start == end) {
        out[start] = arr[start];
        print_graph(graph_file, counter, start, end);
        return;
    }

    int mid = (start + end) / 2;
    crew_prefix(arr, out, start, mid, graph_file, counter);
    crew_prefix(arr, out, mid + 1, end, graph_file, counter);

    // Párhuzamos összeadás
    for (int i = mid + 1; i <= end; i++) {
        out[i] += out[mid];
    }

    print_graph(graph_file, counter, start, end);
}

// GraphViz csomópontok kiírása
void print_graph(FILE *graph_file, int *counter, int start, int end) {
    (*counter)++;
    fprintf(graph_file, "    node%d [label=\"[%d, %d]\"];\n", *counter, start, end);
    if (start < end) {
        fprintf(graph_file, "    node%d -> node%d;\n", *counter, *counter - 1);
    }
}
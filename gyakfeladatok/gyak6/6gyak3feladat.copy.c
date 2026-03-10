void copy(int* src, int* dest, int src_start, int dest_start, int length) {
    for (int i = 0; i < length; i++) {
        dest[dest_start + i] = src[src_start + i];
    }
}
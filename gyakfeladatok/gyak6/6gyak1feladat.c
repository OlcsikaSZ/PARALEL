void beszuro_rendezes(int tomb[], int meret) {
    int i, kulcs, j;
    for (i = 1; i < meret; i++) {
        kulcs = tomb[i];
        j = i - 1;

        while (j >= 0 && tomb[j] > kulcs) {
            tomb[j + 1] = tomb[j];
            j--;
        }
        tomb[j + 1] = kulcs;
    }
}
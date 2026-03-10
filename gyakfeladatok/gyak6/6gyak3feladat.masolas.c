// 2. ciklus
while (i < m) {
    C[p++] = A[i++];
}

// 3. ciklus
while (j < n) {
    C[p++] = B[j++];
}

Helyettesítve copy függvénnyel:

if (i < m)
    copy(A, C, i, p, m - i);

if (j < n)
    copy(B, C, j, p, n - j);
MERGE_PARALLEL(A[0..m-1], B[0..n-1]) -> C[0..m+n-1]
    i = 0, j = 0                // elején kezdők indexei
    k = m - 1, l = n - 1        // végén kezdők indexei
    p = 0, q = m + n - 1        // C tömb eleje és vége

    párhuzamosan:
        // ELEJE: szokásos merge
        amíg i < m és j < n
            ha A[i] <= B[j]
                C[p] = A[i]
                i++, p++
            különben
                C[p] = B[j]
                j++, p++

        // VÉGE: visszafelé merge
        amíg k >= i és l >= j
            ha A[k] > B[l]
                C[q] = A[k]
                k--, q--
            különben
                C[q] = B[l]
                l--, q--
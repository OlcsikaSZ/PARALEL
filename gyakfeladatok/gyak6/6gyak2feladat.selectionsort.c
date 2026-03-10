SelectionSort(tömb A)
    N = A hosszúsága
    ciklus i = 0-tól N - 2-ig
        minIndex = i
        ciklus j = i+1-től N - 1-ig
            ha A[j] < A[minIndex]
                minIndex = j
        csere A[i] <-> A[minIndex]
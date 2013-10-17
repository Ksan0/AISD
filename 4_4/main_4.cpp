#include <stdio.h>


int Abs(int a) {
    return a < 0 ? -a : a;
}


size_t FindIndex(int *A, size_t n, int elem) {
    if (elem <= A[0])
        return 0;

    size_t first = 0, last = n, middle;
    while (first < last)  {
        middle = first + (last - first) / 2;

        if (elem <= A[middle])
            last = middle;
        else
            first = middle + 1;
    }

    if (middle == 0) {
        if (Abs(A[0] - elem) <= Abs(A[1] - elem))
            return 0;
        else
            return 1;
    }
    if (middle == n)
        return FindIndex(A, n, A[n-1]);
    if ( Abs(A[middle] - elem) >= Abs(A[middle-1] - elem) )
        return FindIndex(A, n, A[middle-1]);
    if (middle != n-1 && Abs(A[middle] - elem) > Abs(A[middle+1] - elem))
        return middle + 1;

    return middle;
}


int main(int argc, char *argv[]) {
    size_t n, m;
    scanf("%d %d", &n, &m);

    int *A = new int[n];
    for (size_t i = 0; i < n; i++)
        scanf("%d", A + i);

    int b;
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &b);
        printf("%d ", FindIndex(A, n, b));
    }
    return 0;
}

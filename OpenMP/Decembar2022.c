#include <stdio.h>
#include <omp.h>

#define N 100

void main() {

    int prod = 1;
    int offset = 5;
    int a[N];
    int b[N];
    int c[N * 2];
    int x[N];
    int pom[N];
    int i;
    /*for (int j = 0; j < N; j++) {
        x[j] = j + 1;
    }*/

#pragma omp parallel for private(i) reduction(*:prod)
    for (i = 0; i < N; i++) {
        pom[i] = b[i] * c[offset + N - i - 1];
        prod = prod * x[i];
    }

    for (int i = 0; i < N; i++) {
        a[i] += a[i + 1];
    }
    
}
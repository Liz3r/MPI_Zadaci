#include <stdio.h>
#include <omp.h>

#define N 8
#define M 6

void main() {

    int x = 0;

    int a[N][M];
    int b[N][M];

    //inicijalizacija
    printf("b init:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = i * N + j + 11;
            b[i][j] = i * N + j + 45;
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //---------------
    double time = omp_get_wtime();
   

    int i, j;
#pragma omp parallel for private(i,j) reduction(+:x)
    for (j = 0; j < M; j++) {
        for (i = 2; i < N; i++) {
            x += a[i][j];
            b[i][j] = 4 * b[i - 2][j];
        }
    }


    time = omp_get_wtime() - time;
    printf("\nTime: %lf\n", time);

    printf("b:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    printf("\nx = %d",x);
}

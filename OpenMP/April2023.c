#include <stdio.h>
#include <omp.h>

#define n 80
#define m 60
void main() {
    //omp_set_num_threads(2);

    int A[n][m];
    int B[m][n];
    //A
    printf("Matrica A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = i * n + j + 1;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    //B
    printf("Matrica B:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = i * m + j + 1;
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    double time = omp_get_wtime();

    //mnozenje
    int C[n][n];

    for (int p = 0; p < n; p++) {
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < m; j++) {
                sum += A[p][j] * B[j][i];
            }
            C[p][i] = sum;
        }
    }
    time = omp_get_wtime() - time;
    printf("\nTime seq: %lf\n", time);
  
    printf("Matrica C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }


    int i,p,j;

    time = omp_get_wtime();
#pragma omp parallel shared(A,B,C) private(p,i,j)
    {
#pragma omp for 
        for (p = 0; p < n; p++) {
            for (i = 0; i < n; i++) {
                C[p][i] = 0;
                for (j = 0; j < m; j++) {
                    C[p][i] += A[p][j] * B[j][i];
                }
            }
        }
    }
    time = omp_get_wtime() - time;
    printf("\nTime paralelno: %lf\n", time);

    printf("Matrica C Paralelno:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}
  

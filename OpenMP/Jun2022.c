#include <stdio.h>
#include <omp.h>

#define N 8

void main() {

    int x[N], y[N], z[N];
    int g = 0;

    //inicijalizacija
    for (int i = 0; i < N; i++) {
        y[i] = i + 1;
        x[i] = 10*i + 1;
        z[i] = 100 * i + 1;
    }

    //ova petlja treba da se paralelizuje
    /*for (int i = 1; i < N; i++) {
        y[i] = y[i] + x[i - 1];
        x[i] = x[i] + z[i];
        g += z[i - 1];
    }*/


    //--------------------print-------
    //print x;
    printf("\nx: ");
    for (int i = 0; i < N; i++)
        printf("%d ", x[i]);
    printf("\n");
    //print y;
    printf("\ny: ");
    for (int i = 0; i < N; i++) 
        printf("%d ", y[i]);
    printf("\n");
    //print z;
    printf("\nz: ");
    for (int i = 0; i < N; i++)
        printf("%d ", z[i]);
    printf("\n");
    printf("g: %d\n", g);
    //--------------------------------
  
    //paralelizovano
    int i;
    y[1] = y[1] + x[0];
#pragma omp parallel for reduction(+:g)
    for (i = 1; i < N-1; i++) {
        x[i] = x[i] + z[i];
        y[i+1] = y[i+1] + x[i];
        g += z[i-1];
    }
    x[N-1] = x[N-1] + z[N-1];
    g += z[N - 2];

    //--------------------print-------
    //print x; 3613
    printf("\nx: ");
    for (int i = 0; i < N; i++)
        printf("%d ", x[i]);
    printf("\n");
    //print y;
    printf("\ny: ");
    for (int i = 0; i < N; i++)
        printf("%d ", y[i]);
    printf("\n");
    //print z;
    printf("\nz: ");
    for (int i = 0; i < N; i++)
        printf("%d ", z[i]);
    printf("\n");
    printf("g: %d\n", g);
    //--------------------------------
}
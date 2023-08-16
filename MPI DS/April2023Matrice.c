#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define m 12
#define n 8
#define k 16

#define q 4 
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[m][n];
	int B[n][k];
	int C[m][k];

	int mojeKolone[q][n];
	int mojeC[m][k];

	if (myRank == 0) {

		printf("Matrica A:\n");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * m + j + 1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("Matrica B:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				B[i][j] = i * n + j + 11;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		for (int i = 1; i < np; i++) {
			MPI_Send(&A[0][0], m * n, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

	
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < n; j++) {
				mojeKolone[i][j] = B[j][i];
			}
		}

		int slanjeA[q][n];
		
		for (int p = 1; p < np; p++) {
			for (int i = 0; i < q; i++) {
				for (int j = 0; j < n; j++) {
					slanjeA[i][j] = B[j][i + p * q];
				}
			}
			MPI_Send(&slanjeA[0][0], q * n, MPI_INT, p, 1, MPI_COMM_WORLD);
		}
	}
	else {
			MPI_Recv(&A[0][0], m * n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			MPI_Recv(&mojeKolone[0][0], n * q, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			mojeC[i][j] = 0;
		}
	}

	for (int p = 0; p < m; p++) {

		for (int i = 0; i < q; i++) {
			for (int j = 0; j < n; j++) {
				mojeC[p][myRank*q + i] += A[p][j] * mojeKolone[i][j];
			}
		}
	}


	MPI_Reduce(&mojeC[0][0], &C[0][0], m * k, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myRank == 0) {

		printf("Proces %d, C:\n", myRank);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				printf("%d ", C[i][j]);
			}
			printf("\n");
		}
	}


	MPI_Finalize();
}

//mpiexec -n 4 ...
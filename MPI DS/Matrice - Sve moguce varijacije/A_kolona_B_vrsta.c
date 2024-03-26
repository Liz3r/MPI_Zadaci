#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 10
#define k 12
#define q 2

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[n][k];
	int B[k][n];
	int C[n][n];

	int mojeKoloneA[n][q];
	int mojeVrsteB[q][n];

	int mojeC[n][n];



	if (myRank == 0) {

		printf("Matrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				A[i][j] = i * n + j + 1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}

		printf("Matrica B:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = i * k + j + 1;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}


		for (int i = 0; i < q; i++) {
			for (int j = 0; j < n; j++) {
				mojeKoloneA[j][i] = A[j][i];
			}
		}

		int slanje[n][q];
		for (int proc = 1; proc < np; proc++) {
		
			for (int i = 0; i < q; i++) {
				for (int j = 0; j < n; j++) {
					slanje[j][i] = A[j][(proc * q) + i];
				}
			}
			MPI_Isend(&slanje[0][0], q * n, MPI_INT, proc, 1, MPI_COMM_WORLD, &req);
		}
	}
	else {

		MPI_Recv(&mojeKoloneA[0][0], n * q, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	MPI_Scatter(&B[0][0], q * n, MPI_INT, &mojeVrsteB[0][0], q * n, MPI_INT, 0, MPI_COMM_WORLD);

	for (int p = 0; p < n; p++) {
		for (int i = 0; i < n; i++) {
			mojeC[p][i] = 0;
			for (int j = 0; j < q; j++) {
				mojeC[p][i] += mojeKoloneA[p][j] * mojeVrsteB[j][i];
			}
		}
	}

	MPI_Reduce(&mojeC[0][0], &C[0][0], n * n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myRank == 0) {
		printf("\nC konacno:\n");
		for (int p = 0; p < n; p++) {
			for (int i = 0; i < n; i++) {
				printf("%d ", C[p][i]);
			}
			printf("\n");
		}

	}

	MPI_Finalize();
}

//mpiexec -n 6 mpi_build.exe
#include<mpi.h>
#include<stdio.h>
#include <stdlib.h>
#include <climits>

#define n 8
#define k 6
#define q 2
//A[n][k]
//B[k][n]

void main(int argc, char* argv[]) {

	int myRank, np, root = 0;
	MPI_Request req;
	MPI_Status stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int A[n][k];
	int B[k][n];
	int C[n][n];
	int rezultat[n][n];

	int mojeKolone[q][n];
	int mojeVrste[q][n];

	if (myRank == root) {

		printf("\nA:");
		for (int i = 0; i < n; i++) {
			printf("\n");
			for (int j = 0; j < k; j++) {
				A[i][j] = i * n + j + 1;
				printf("%d ", A[i][j]);
			}
		}

		printf("\nB:");
		for (int i = 0; i < k; i++) {
			printf("\n");
			for (int j = 0; j < n; j++) {
				B[i][j] = i * k + j + 1;
				printf("%d ", B[i][j]);
			}
		}
		//proces 0 uzima svoje kolone
		printf("\nProces 0 Kolone: \n");
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < n; j++) {
				mojeKolone[i][j] = A[j][i];
				printf("%d ", mojeKolone[i][j]);
			}
			printf("\n");
		}

		printf("\nProces 0 Vrste: \n");
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < n; j++) {
				mojeVrste[i][j] = B[i][j];
				printf("%d ", mojeVrste[i][j]);
			}
			printf("\n");
		}
		//svakom procesu
		int kolona[n];
		for (int i = 1; i < k / q && i < np; i++) {

			for (int j = 0; j < q; j++) {
				for (int g = 0; g < n; g++) {
					kolona[g] = A[g][i * q + j];
				}
				MPI_Send(&kolona[0], n, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
		}
		//vrste B
		for (int i = 1; i < k / q && i < np; i++) {

			for (int j = 0; j < q; j++) {
				MPI_Send(&B[i * q + j][0], n, MPI_INT, i, 1, MPI_COMM_WORLD);
			}
		}

	}
	if (myRank < k / q && myRank > 0) {
		for (int j = 0; j < q; j++) {
			MPI_Recv(&mojeKolone[j][0], n, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
		}

		for (int j = 0; j < q; j++) {
			MPI_Recv(&mojeVrste[j][0], n, MPI_INT, 0, 1, MPI_COMM_WORLD, &stat);
		}

		printf("\nProces %d Kolone:\n", myRank);
		for (int i = 0; i < q; i++) {
			printf("\n");
			for (int j = 0; j < n; j++) {
				printf("%d ", mojeKolone[i][j]);
			}
		}

		printf("\nProces %d Vrste:\n", myRank);
		for (int i = 0; i < q; i++) {
			printf("\n");
			for (int j = 0; j < n; j++) {
				printf("%d ", mojeVrste[i][j]);
			}
		}
	}

	//-----------mnozenje
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
		}
	}
	for (int g = 0; g < q; g++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				C[i][j] += mojeKolone[g][i] * mojeVrste[g][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			MPI_Reduce(&C[i][j], &rezultat[i][j], 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		}
	}

	if (myRank == 0) {
		printf("\nRezultat:\n");
		for (int i = 0; i < n; i++) {
			printf("\n");
			for (int j = 0; j < n; j++) {
				printf("%d ", rezultat[i][j]);
			}
		}
	}


	MPI_Finalize();
}

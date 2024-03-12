#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define k 8
#define m 6
#define n 10
#define r 2

void main(int argc, char* argv[]) {

	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[k][m];
	int B[m][n];
	int C[k][n];

	int mojeKolone[r][m];

	int mojiRezultati[r][n];
	int mojeKoloneSuma[m];
	int mojMin = 999999;

	int kolonaSuma[m];

	int minProcRank;


	if (myRank == root) {

		printf("Matrica A:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < m; j++) {
				A[i][j] = i * k + j + 1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("Matrica B:\n");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = i * m + j + 1;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
		printf("\n");

	}
	MPI_Scatter(&A[0][0], r * m, MPI_INT, &mojeKolone[0][0], r * m, MPI_INT, root, MPI_COMM_WORLD);
	MPI_Bcast(&B[0][0], m * n, MPI_INT, 0, MPI_COMM_WORLD);


	//-----------------------
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < n; j++) {
			mojiRezultati[i][j] = 0;
			for (int q = 0; q < m; q++) {
				mojiRezultati[i][j] += mojeKolone[i][q] * B[q][j];
			}
		}
	}

	for (int i = 0; i < m; i++) {
		mojeKoloneSuma[i] = 0;
		for (int j = 0; j < r; j++) {
			mojeKoloneSuma[i] += mojeKolone[j][i];
		}
	}

	//najmanji element za svaki proces
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < m; j++) {
			if (mojeKolone[i][j] < mojMin)
				mojMin = mojeKolone[i][j];
		}
	}

	struct {
		int value;
		int rank;
	} in, out;

	in.rank = myRank;
	in.value = mojMin;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

	minProcRank = out.rank;

	MPI_Reduce(&mojeKoloneSuma[0], &kolonaSuma[0], m, MPI_INT, MPI_SUM, minProcRank, MPI_COMM_WORLD);

	MPI_Gather(&mojiRezultati[0][0], r * n, MPI_INT, &C[0][0], r * n, MPI_INT, minProcRank, MPI_COMM_WORLD);

	printf("Proces %d moji rezultati:\n", myRank);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", mojiRezultati[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Proces %d moje sume:\n", myRank);
	for (int j = 0; j < m; j++) {
		printf("%d ", mojeKoloneSuma[j]);
	}
	printf("\n");

	if (myRank == minProcRank) {
		printf("Proces %d konacni rezultati:\n", myRank);
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", C[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	MPI_Finalize();
}
#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 16
#define k 8
#define q 2

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[n][k];
	int B[k][n];

	int mojeKoloneA[n][q];
	int mojeVrsteB[q][n];

	int mojiRezultati[n][n];

	int mojeSumeKolonaB[n];
	int sumeKolonaB[n];
	
	int mojMax = -999999;

	int prikazProc;

	int C[n][n];

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



		for (int i = 0; i < n; i++) {
			for (int j = 0; j < q; j++) {
				mojeKoloneA[i][j] = A[i][j];
			}
		}

		int slanjeA[n][q];
		for (int p = 1; p < np; p++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < q; j++) {
					slanjeA[i][j] = A[i][p*q+j];
				}
			}

			MPI_Send(&slanjeA[0][0], q * n, MPI_INT, p, 2, MPI_COMM_WORLD);
		}

	}
	else {

		MPI_Recv(&mojeKoloneA[0][0], q * n, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	MPI_Scatter(&B[0][0], q * n, MPI_INT, &mojeVrsteB, q * n, MPI_INT, 0, MPI_COMM_WORLD);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mojiRezultati[i][j] = 0;
		}
	}
	for (int o = 0; o < q; o++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mojiRezultati[i][j] += mojeKoloneA[i][o] * mojeVrsteB[o][j];
			}
		}
	}

	//sume kolona B

	for (int i = 0; i < n; i++) {
		mojeSumeKolonaB[i] = 0;
		for (int j = 0; j < q; j++) {
			mojeSumeKolonaB[i] += mojeVrsteB[j][i];
			//odmah se nadje i maximalna vrednost matrice B svakog procesa
			if (mojMax < mojeVrsteB[j][i])
				mojMax = mojeVrsteB[j][i];
		}
	}

	struct {
		int val;
		int rank;
	}in,out;

	in.val = mojMax;
	in.rank = myRank;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);

	prikazProc = out.rank;

	MPI_Reduce(&mojeSumeKolonaB[0], &sumeKolonaB[0], n, MPI_INT, MPI_SUM, prikazProc, MPI_COMM_WORLD);

	MPI_Reduce(&mojiRezultati[0][0], &C[0][0], n * n, MPI_INT, MPI_SUM, prikazProc, MPI_COMM_WORLD);

	if (myRank == prikazProc) {
		printf("Rezultat P%d C[][]:\n",myRank);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ",C[i][j]);
			}
			printf("\n");
		}

		printf("Sume kolona B:\n");
		for (int i = 0; i < n; i++) {
			printf("%d ", sumeKolonaB[i]);
		}
	}

	MPI_Finalize();
}

//mpiexec -n 4 mpi_build.exe
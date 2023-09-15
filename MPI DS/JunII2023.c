#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 8
#define k 16
#define q 4
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[n][k];
	int B[k][n];
	int C[n][n];
	int prikazC[n][n];

	int mojeKolone[q][n];
	int mojeVrste[q][n];

	int proizvodKolona[q];
	int mojMax = 0;

	int prikazRank;

	int mojiRezultati[q][q];

	unsigned long koloneProizvodB[n];
	unsigned long koloneProizvodBPrikaz[n];

	if (myRank == 0) {

		printf("Matrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				A[i][j] = i * n + j + 1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("Matrica B:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = i * n + j + 21;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		//---------------------------------------


		int slanjeA[q][n];
		//nesto se ubaguje kad se salje redom (i =  0 -> np) pa proces 0 dobije pogresne vrednosti
		for (int i = (np-1); i >= 0; i--) {
			for (int j = 0; j < q; j++) {
				for (int p = 0; p < n; p++) {
					slanjeA[j][p] = A[p][(i * q + j)%k];
				}
			}
			MPI_Isend(&slanjeA[0][0], q * n, MPI_INT, i, 0, MPI_COMM_WORLD, &req);
			MPI_Isend(&B[(i * q)/n][0], q * n, MPI_INT, i, 1, MPI_COMM_WORLD, &req);
		}

	}

	MPI_Recv(&mojeKolone[0][0], q * n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&mojeVrste[0][0], q * n, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	

	//deo proizvoda elemenata  vrste matrice b
	// i max element u vrstama iz b koje poseduje n-ti proces
	for (int i = 0; i < n; i++) {
		koloneProizvodB[i] = 1;
		koloneProizvodBPrikaz[i] = 1;
		for (int j = 0; j < q; j++) {
			koloneProizvodB[i] *= mojeVrste[j][i];
			if (mojMax < mojeVrste[i][j]) {
				mojMax = mojeVrste[i][j];
			}
		}
	}
	
	printf("Proces %d moj max element: %d\n", myRank, mojMax);
	
	struct {
		int rank;
		int value;
	}in,out;

	in.rank = myRank;
	in.value = mojMax;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);
	
	prikazRank = out.rank;
	
	if (myRank == prikazRank) {
		printf("proces koji prikazuje: %d\n", prikazRank);
	}
	
	/*for (int i = 0; i < n; i++) {
		printf("%d ", koloneProizvodB[i]);
	}
	printf("\n");*/
	
	//MPI_Reduce(&koloneProizvodB[0], &koloneProizvodBPrikaz[0], n, MPI_UNSIGNED_LONG, MPI_PROD, prikazRank, MPI_COMM_WORLD);
	
	if (myRank == prikazRank) {
		printf("proces %d proizvod elemenata u kolonama iz B: \n", prikazRank);
		for (int i = 0; i < n; i++) {
			printf("%d ", koloneProizvodBPrikaz[i]);
		}
		printf("\n");
	}
	
	//----------------

	/*printf("Proces %d, moje kolone:\n", myRank);
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", mojeKolone[i][j]);
		}
		printf("\n");
	}
	printf("Proces %d, moje vrste:\n", myRank);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < q; j++) {
			printf("%d ", mojeVrste[j][i]);
		}
		printf("\n");
	}*/

	
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < q; j++) {
			C[(myRank / q) + j][(myRank % q) + i] = 0;
			for (int p = 0; p < n; p++) {
				C[myRank/q + j][myRank%q + i] += mojeKolone[i][p] * mojeVrste[j][p];
			}
		}
	}
	
	MPI_Reduce(&C[0][0], &prikazC[0][0], n* n, MPI_INT, MPI_MAX, prikazRank, MPI_COMM_WORLD);


	if (myRank == prikazRank) {
		printf("Konacno C:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", prikazC[i][j]);
			}
			printf("\n");
		}
	}
	
	MPI_Finalize();
}

//mpiexec -n 16 ...
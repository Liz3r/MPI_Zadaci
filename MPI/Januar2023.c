#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>


#define n 8
#define k 2

//Paralelni sistemi - Januarski 2023  // 2. zadatak a)

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	//izvedeni tipovi
	MPI_Datatype vrste;
	MPI_Type_contiguous(n*k, MPI_INT, &vrste);
	MPI_Type_commit(&vrste);

	MPI_Datatype kolone, koloneExtended;
	MPI_Type_vector(n, 1, n, MPI_INT, &kolone);
	MPI_Type_commit(&kolone);

	MPI_Type_create_resized(kolone, 0, 1 * sizeof(int), &koloneExtended);
	MPI_Type_commit(&koloneExtended);
	//------------------------------- a)

	if (myRank == 0) {

		//Inicijalizacija matrica
		int A[n][n];
		int B[n][n];

		printf("Matrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * n + j + 11;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}

		printf("Matrica B:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = i * n + j + 137;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
		//------------------------------
		//smatrati da su procesi rasporedjeni kao u matrici
		int brojProcesaPoVrsti = (int) sqrt(np);
		//slanje
		for (int i = 0; i < np; i++) {
			MPI_Isend(&A[(i/brojProcesaPoVrsti)*2][0], 1, vrste, i, 0, MPI_COMM_WORLD,&req);
			MPI_Isend(&B[0][(i % brojProcesaPoVrsti) * 2], k, koloneExtended, i, 1, MPI_COMM_WORLD, &req);
		}

	}

	int mojeVrsteA[k][n];
	int mojeKoloneB[k][n];

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Recv(&mojeVrsteA[0][0], n*k, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&mojeKoloneB[0][0], n * k, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//----------------------------------------
	//izracunavanje rezultata svakog procesa

	int mojiRezultati[k][k];

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			int suma = 0;
			for (int p = 0; p < n; p++) {
				suma += mojeVrsteA[i][p] * mojeKoloneB[j][p];
			}
			mojiRezultati[i][j] = suma;
		}
	}
	//pronalazenje maksimalnog elementa
	struct {
		int value;
		int rank;
	}in,out;

	int mojMaxElement = 0;

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (mojiRezultati[i][j] > mojMaxElement)
				mojMaxElement = mojiRezultati[i][j];
		}
	}

	in.value = mojMaxElement;
	in.rank = myRank;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);
	//rank i vrednost tog procesa su u out
	if(myRank == out.rank)
		printf("Proces koji sadrzi najveci element u rezultatu: %d\nVrednost: %d", out.rank,out.value);

	//sakupljanje rezultata u master procesu
	int C[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
		}
	}

	int myRow = myRank/(n/k);
	int myCol = myRank%(n/k);

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			C[myRow * k + i][myCol * k + j] = mojiRezultati[i][j];
		}
	}

	int rezultatMatrica[n][n];

	MPI_Reduce(&C[0][0], &rezultatMatrica[0][0], n* n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (myRank == 0) {
		printf("Rezultat mnozenja:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", rezultatMatrica[i][j]);
			}
			printf("\n");
		}
	}
	
	MPI_Finalize();
}


//mpiexec -n 16 Januar2023.exe
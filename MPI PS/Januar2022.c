#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 8
#define q 4
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;


	int A[n][n];
	int B[n][n];
	int C[n][n];
	int CFinal[n][n];

	int mojeKolone[n / q][n];
	int mojiRedovi[n / q][n];
	int mojiRezultati[n/q][n/q];
	

	int myRow = myRank / q;
	int myCol = myRank % q;
	MPI_Comm col_comm, row_comm;
	MPI_Comm_split(MPI_COMM_WORLD, myRow, 0, &row_comm);
	MPI_Comm_split(MPI_COMM_WORLD, myCol, 1, &col_comm);

	MPI_Datatype col,colRes,sendCol, sendColRes, sendRow, sendRowRes;
	MPI_Type_vector(n, 1, n, MPI_INT, &col);//jedna kolona
	MPI_Type_create_resized(col, 0, sizeof(int), &colRes);
	MPI_Type_vector(n / q, 1, q, colRes, &sendCol);//n/q kolona
	MPI_Type_create_resized(sendCol, 0, sizeof(int), &sendColRes);
	MPI_Type_commit(&sendColRes); //ceo blok iz matrice koji treba da se posalje

	MPI_Type_vector(n / q, n, n * q, MPI_INT, &sendRow); //blok redova sa razmakom q
	MPI_Type_create_resized(sendRow, 0, n*sizeof(int), &sendRowRes);
	MPI_Type_commit(&sendRowRes);

	MPI_Datatype jedanRed,jedanRedRes,rezultatType,rezultatTypeRes,sendRezultat,sendRezultatRes;
	MPI_Type_vector(n / q, 1, q, MPI_INT, &jedanRed);
	MPI_Type_create_resized(jedanRed, 0, sizeof(int)*n, &jedanRedRes);
	MPI_Type_vector(n / q, 1, q, jedanRedRes, &rezultatType);
	MPI_Type_create_resized(rezultatType, 0, sizeof(int), &rezultatTypeRes);
	MPI_Type_commit(&rezultatTypeRes);

	if (myRank == 0) {

		printf("\nMatrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * n + j + 1;
				printf("%d ",A[i][j]);
			}
			printf("\n");
		}

		printf("\nMatrica B:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = i * n + j + 81;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
	}

	if (myRow == 0) 
		MPI_Scatter(&B[0][0], 1, sendColRes, &mojeKolone[0][0], (n / q) * n, MPI_INT, 0, row_comm);	
	
	MPI_Bcast(&mojeKolone[0][0], (n / q) * n, MPI_INT, 0, col_comm);

	if (myCol == 0) 
		MPI_Scatter(&A[0][0], 1, sendRowRes, &mojiRedovi[0][0], (n / q) * n, MPI_INT, 0, col_comm);
	
	MPI_Bcast(&mojiRedovi[0][0], (n / q) * n, MPI_INT, 0, row_comm);

	//generisanje rezultata
	for (int i = 0; i < n / q; i++) {
		for (int j = 0; j < n / q; j++) {
			mojiRezultati[j][i] = 0;
			for (int p = 0; p < n; p++) {
				mojiRezultati[j][i] += mojeKolone[i][p] * mojiRedovi[j][p];
			}
		}
	}
	//-----

	
	MPI_Gather(&mojiRezultati[0][0], (n / q) * (n / q), MPI_INT, &C[myRow][0], 1, rezultatTypeRes, 0, row_comm);

	if (myCol == 0) {
		MPI_Reduce(&C[0][0], &CFinal[0][0], n * n, MPI_INT, MPI_MAX, 0, col_comm);
	}
	if (myRank == 0) {
		printf("\nProces %d C:\n", myRank);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", CFinal[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
}
//mpiexec -n 16 Januar2022.exe
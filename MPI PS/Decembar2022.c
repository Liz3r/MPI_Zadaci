#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define q 4
#define n 8

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[n][n];
	int B[n][n];
	int C[n][n];

	int mojeVrste[n/q][n];
	int mojeKolone[n][n/q];

	int mojiRezultati[n / q][n / q];

	if (myRank == 0) {

		//init A
		printf("\nMatrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * n + j + 1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		//init B
		printf("\nMatrica B:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = ((i * n + j + 1)*139)%100;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	//komunikatori za kolone i vrste
	MPI_Comm col_comm, row_comm;
	int myCol = myRank % 4;
	int myRow = myRank / 4;
	MPI_Comm_split(MPI_COMM_WORLD, myCol, 0, &col_comm);
	MPI_Comm_split(MPI_COMM_WORLD, myRow, 0, &row_comm);

	int vrstaKolonaPoProcesu = n / q;

	MPI_Datatype vrste;
	MPI_Type_vector(vrstaKolonaPoProcesu, n, q * n, MPI_INT, &vrste);
	MPI_Type_commit(&vrste);

	if (myRank == 0) {
		for (int i = 0; i < q; i++) {
			MPI_Isend(&A[i][0], 1, vrste, i, 0, row_comm,&req);
		}
	}
	if (myRow == 0) {
		MPI_Recv(&mojeVrste[0][0], (n / q) * n, MPI_INT, 0, 0, row_comm, MPI_STATUS_IGNORE);
	}
	MPI_Bcast(&mojeVrste[0][0], (n / q) * n, MPI_INT, 0, col_comm);

	MPI_Datatype kolone,jednaKolona;
	MPI_Type_vector(n*(n/q),1,q, MPI_INT, &jednaKolona);
	MPI_Type_commit(&jednaKolona);

	if (myRank == 0) {
		for (int i = 0; i < q; i++) {
			MPI_Isend(&B[0][i], 1, jednaKolona, i, 1, col_comm, &req);
		}
	}
	if (myCol == 0) {
		MPI_Recv(&mojeKolone[0][0], (n / q) * n, MPI_INT, 0, 1, col_comm, MPI_STATUS_IGNORE);
	}
	MPI_Bcast(&mojeKolone[0][0], (n / q) * n, MPI_INT, 0, row_comm);

	//rezultati za svaki proces
	for (int i = 0; i < n/q; i++) {
		for (int j = 0; j < n / q; j++) {
			mojiRezultati[i][j] = 0;
			for (int k = 0; k < n; k++) {
				mojiRezultati[i][j] += mojeVrste[i][k] * mojeKolone[k][j];
			}
		}
	}

	//slanje rezultata glavnom procesu

	MPI_Isend(&mojiRezultati[0], (n / q) * (n / q), MPI_INT, 0, 3, MPI_COMM_WORLD, &req);

	if (myRank == 0) {
		MPI_Datatype recvType, recvTypeOne, recvTypeOneResized;
		MPI_Type_vector((n / q), 1, q, MPI_INT, &recvTypeOne);
		MPI_Type_create_resized(recvTypeOne, 0, sizeof(int) * n, &recvTypeOneResized);
		MPI_Type_vector((n / q), 1, q, recvTypeOneResized, &recvType);
		MPI_Type_commit(&recvType);
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < q; j++) {
				MPI_Recv(&C[j][i], 1, recvType, i * q + j, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
	}

	//------------------------------------------
	printf("Proces %d, mojeVrste:\n", myRank);
	for (int i = 0; i < n / q; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", mojeVrste[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Proces %d, mojeKolone:\n", myRank);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n/q; j++) {
			printf("%d ", mojeKolone[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("\n");
	printf("Proces %d, mojiRezultati:\n", myRank);
	for (int i = 0; i < n/q; i++) {
		for (int j = 0; j < n / q; j++) {
			printf("%d ", mojiRezultati[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	MPI_Barrier(MPI_COMM_WORLD);
	if (myRank == 0) {
		printf("Proces %d, konacni rezultati:\n", myRank);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", C[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	MPI_Finalize();
}
//mpiexec -n 16 Decembar2022.exe
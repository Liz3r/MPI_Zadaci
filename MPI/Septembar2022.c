#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 8
//broj procesa = q * q
#define q 4
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[n][n];
	int b[n];
	int c[n];

	int mojiMinElement = 9999;
	int minElProcRank;
	int mojiElementi[n / q][n / q];
	int mojiElementiVektor[n / q];
	int mojiRezultati[n / q];
	int rezultatiKonacno[n / q];

	MPI_Datatype oneRow,oneRowRes,oneRowSend,sendType;
	MPI_Type_vector(n / q, 1, q, MPI_INT, &oneRow);
	MPI_Type_create_resized(oneRow, 0, sizeof(int), &oneRowSend);
	MPI_Type_commit(&oneRowSend);
	MPI_Type_create_resized(oneRow, 0, n * sizeof(int), &oneRowRes);
	MPI_Type_vector(n / q, 1, q, oneRowRes, &sendType);
	MPI_Type_commit(&sendType);

	MPI_Comm col_comm, row_comm;
	int myRow, myCol;
	myRow = myRank / q;
	myCol = myRank % q;
	MPI_Comm_split(MPI_COMM_WORLD, myRow, 0, &row_comm);
	MPI_Comm_split(MPI_COMM_WORLD, myCol, 0, &col_comm);


	if (myRank == 0) {
		//inicijalizacija i stampanje
		printf("\nMatrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * n + j + 1;
				printf("%d ", A[i][j]);
			}
			b[i] = i + 10;
			printf("\n");
		}
		printf("\n");
		printf("Vektor b:\n");
		for (int i = 0; i < n; i++) {
			printf("%d ", b[i]);
		}
		printf("\n");

		
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < q; j++) {
				MPI_Isend(&A[i][j], 1, sendType, i * q + j, 0, MPI_COMM_WORLD, &req);
			}
		}
	}
	MPI_Recv(&mojiElementi[0], (n / q) * (n / q), MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	if (myRow == 0) {
		MPI_Scatter(&b[0], 1, oneRowSend, &mojiElementiVektor[0], n / q, MPI_INT, 0, row_comm);
	}
	MPI_Bcast(&mojiElementiVektor[0], n / q, MPI_INT, 0, col_comm);
	
	//min element za proces + stampanje primljenih elemenata
	printf("\nProces %d:\n", myRank);
	for (int i = 0; i < n/q; i++) {
		for (int j = 0; j < n/q; j++) {
			if (mojiElementi[i][j] < mojiMinElement)
				mojiMinElement = mojiElementi[i][j];
			printf("%d ", mojiElementi[i][j]);
		}
		printf("\n");
	}
	printf("\nmin element %d\n", mojiMinElement);
	printf("\n");

	printf("\nProces %d:\n", myRank);
	for (int i = 0; i < n / q; i++) {
		printf("%d ", mojiElementiVektor[i]);
	}
	printf("\n");
	//----------------------------------------------


	for (int i = 0; i < n / q; i++) {
		mojiRezultati[i] = 0;
		for (int j = 0; j < n / q; j++) {
			mojiRezultati[i] += mojiElementiVektor[j] * mojiElementi[i][j];
		}
	}
	printf("\nProces %d rezultati:\n", myRank);
	for (int i = 0; i < n / q; i++) {
			printf("%d ", mojiRezultati[i]);
	}
	printf("\n");
	struct {
		int rank;
		int value;
	}in,out;

	in.rank = myRank;
	in.value = mojiMinElement;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

	//proces sa najmanjim elementom u out.rank
	minElProcRank = out.rank;

	MPI_Reduce(&mojiRezultati[0], &rezultatiKonacno[0], n / q, MPI_INT, MPI_SUM,0, row_comm);

	if(myCol == 0)
		MPI_Gather(&rezultatiKonacno[0], n / q, MPI_INT, &c[0], 1, oneRowSend, minElProcRank, col_comm);

	if (myRank == minElProcRank) {
		printf("proces %d , konacni rezultat:\n", myRank);
		for (int i = 0; i < n; i++) {
			printf("%d ", c[i]);
		}
		printf("\n");
	}
	

	MPI_Finalize();
}
//mpiexec -n 16 Septembar2022.exe
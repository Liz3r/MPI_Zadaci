#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define k 8
//broj procesa = q * q
#define q 4
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[k][k];
	int b[k];
	int c[k];

	MPI_Datatype sendType,sendTypeRes;
	MPI_Type_vector(2, 2, 4 * k, MPI_INT, &sendType);
	MPI_Type_create_resized(sendType, 0, 2 * sizeof(int), &sendTypeRes);
	MPI_Type_commit(&sendTypeRes);

	MPI_Datatype sendTypeVector, sendTypeVectorRes;
	MPI_Type_vector(2, 1, 4 , MPI_INT, &sendTypeVector);
	MPI_Type_create_resized(sendTypeVector, 0, sizeof(int), &sendTypeVectorRes);
	MPI_Type_commit(&sendTypeVectorRes);

	int mojiElementi[k/q][k/q];
	int mojiElementiVektor[k/q];
	int mojiRezultati[k / q];
	int mojiRezultatiKolona[k / q];

	MPI_Comm col_comm,row_comm;
	int myCol = myRank % q;
	int myRow = myRank / q;
	MPI_Comm_split(MPI_COMM_WORLD, myCol, 0, &col_comm);
	MPI_Comm_split(MPI_COMM_WORLD, myRow, 0, &row_comm);



	if (myRank == 0) {
		//inicijalizacija i stampanje
		printf("\nMatrica A:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				A[i][j] = i * k + j + 1;
				printf("%d ", A[i][j]);
			}
			b[i] = i + 10;
			printf("\n");
		}
		printf("\n");
		printf("Vektor b:\n");
		for (int i = 0; i < k; i++) {
			printf("%d ", b[i]);
		}
		printf("\n");

		
	}
	MPI_Scatter(&A[0][0], 1, sendTypeRes, &mojiElementi[0], q, MPI_INT, 0, MPI_COMM_WORLD);
	if(myRow == 0)
		MPI_Scatter(&b[0], 1, sendTypeVectorRes, &mojiElementiVektor[0], k / q, MPI_INT, 0, row_comm);
	MPI_Bcast(&mojiElementiVektor[0], 2, MPI_INT, 0, col_comm);

	for (int i = 0; i < k / q; i++) {
		mojiRezultati[i] = 0;
		for (int j = 0; j < k / q; j++) {
			mojiRezultati[i] += mojiElementi[i][j] * mojiElementiVektor[j];
		}
	}

	MPI_Reduce(&mojiRezultati[0],&mojiRezultatiKolona[0],2,MPI_INT,MPI_SUM,0 ,row_comm);
	if (myCol == 0) {
		MPI_Gather(&mojiRezultatiKolona[0], 2, MPI_INT, &c[0], 1, sendTypeVectorRes, 0, col_comm);
	}
	/*printf("\nProces %d mojiElementi:\n",myRank);
	for (int i = 0; i < k/q; i++) {
		for (int j = 0; j < k/q; j++) {
			printf("%d ", mojiElementi[i][j]);
		}
		printf("\n");
	}
	printf("\nProces %d mojiElementiVektor:\n", myRank);
	for (int j = 0; j < k / q; j++) {
		printf("%d ", mojiElementiVektor[j]);
	printf("\n");
	}*/

	if (myRank == 0) {
		printf("\nProces %d konacni rezultat:\n", myRank);
		for (int j = 0; j < k; j++) 
			printf("%d ", c[j]);
		printf("\n");
		
	}
	MPI_Finalize();
}
//mpiexec -n 16 Oktobar2022.exe
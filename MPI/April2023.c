#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>


#define n 8
#define q 4

//Paralelni sistemi - Aprilski 2023  // 2. zadatak a)

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int A[n][n];
	int b[n];

	MPI_Datatype sendType;

	int blockLengths[] = { 1,1,1,1 };
	int blockDisplacements[] = { 0,4,n,n + 4 };
	MPI_Type_indexed(4, blockLengths, blockDisplacements, MPI_INT, &sendType);
	MPI_Type_commit(&sendType);


	MPI_Datatype vectorSendType;
	MPI_Type_vector(n / q, 1, q, MPI_INT, &vectorSendType);
	MPI_Type_commit(&vectorSendType);

	MPI_Datatype vectorResized;

	MPI_Type_create_resized(vectorSendType, 0, 1* sizeof(int), &vectorResized);
	MPI_Type_commit(&vectorResized);

	if (myRank == 0) {

		//inicijalizacija
		printf("Matrica:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * n + j + 11;
				if (i == 2 && j == 3) {
					A[i][j] = 2;
				}
				printf("%d ", A[i][j]);
			}
			printf("\n");
			b[i] = i * 10;
		}
		printf("Vektor:\n");
		for (int j = 0; j < n; j++) {
			printf("%d ", b[j]);
		}
		//--------------------
		for (int i = 0; i < np; i++) {
			//blok iz matrice
			MPI_Isend(&A[(i / 4) * 2][i % 4], 1, sendType, i, 0, MPI_COMM_WORLD,&req);
			
		}

	}

	int mojiElementi[q];
	MPI_Recv(&mojiElementi[0], q, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


	//slanje vektora pomocu grupnih operacija
	int mojiVektorElementi[n / q];
	MPI_Comm row_comm;
	MPI_Comm col_comm;

	int myRow = myRank / q;
	int myCol = myRank % q;

	MPI_Comm_split(MPI_COMM_WORLD, myRow, 0, &row_comm);
	MPI_Comm_split(MPI_COMM_WORLD, myCol, 0, &col_comm);

	if (myRow == 0) {
		MPI_Scatter(&b[0], 1, vectorResized, &mojiVektorElementi[0], n/q, MPI_INT, 0, row_comm);

	}

	MPI_Bcast(&mojiVektorElementi[0], 2, MPI_INT, 0, col_comm);

	//---------------------

	int rankProcesaKojiPrikazujeRezultat;
	//min element racuna svaki proces za sebe
	int mojMinElement = INT_MAX;
	for (int i = 0; i < q; i++) {
		if (mojiElementi[i] < mojMinElement)
			mojMinElement = mojiElementi[i];
	}
	//printf("Proces %d, min element: %d\n", myRank, mojMinElement);
	struct {
		int value;
		int rank;
	}in,out;
	in.value = mojMinElement;
	in.rank = myRank;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);


	rankProcesaKojiPrikazujeRezultat = out.rank;
	//printf("%d", rankProcesaKojiPrikazujeRezultat);
	//----------------

	int mojiRezultati[n / q];
	for (int j = 0; j < n/q; j++) {
		mojiRezultati[j] = 0;
	}
	
	for (int j = 0; j < q; j++) {
		mojiRezultati[j/2] += mojiElementi[j] * mojiVektorElementi[j % 2];
	}

	int sumiraniRezultatiKolone[n / q];
	
	MPI_Reduce(&mojiRezultati[0], &sumiraniRezultatiKolone[0], 2, MPI_INT, MPI_SUM, rankProcesaKojiPrikazujeRezultat%q, row_comm);
	
	int rezultatVektor[n];
	if (myCol == rankProcesaKojiPrikazujeRezultat%q) {
		/*printf("Konacni rezultati, Proces %d:\n", myRank);
		for (int i = 0; i < n/q; i++) {
			printf("%d ", sumiraniRezultatiKolone[i]);
		}
		printf("\n");*/
		MPI_Gather(&sumiraniRezultatiKolone[0], 2, MPI_INT, &rezultatVektor[0], 2, MPI_INT, rankProcesaKojiPrikazujeRezultat/q, col_comm);
	}

	if (myRank == rankProcesaKojiPrikazujeRezultat) {
		printf("Konacni rezultati, Proces %d:\n", myRank);
		for (int i = 0; i < n; i++) {
			printf("%d ", rezultatVektor[i]);
		}
		printf("\n");
	}

	MPI_Finalize();
}

#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 8
#define k 6
#define l 16


 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	//a)--------------------------------------------------

	int korak = 2;
	int trenutniProc;
	int mojaSuma = myRank;
	int mojPrijem;

	while (korak <= np) {

		trenutniProc = 0;
		while (trenutniProc < np) {
			if (myRank == trenutniProc) {
				MPI_Recv(&mojPrijem,1,MPI_INT,trenutniProc+(korak/2),0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				mojaSuma += mojPrijem;
			}
			if(myRank == trenutniProc + (korak / 2))
			{
				MPI_Send(&mojaSuma, 1, MPI_INT, myRank - (korak / 2), 0, MPI_COMM_WORLD);
			}
			MPI_Barrier(MPI_COMM_WORLD);
			trenutniProc += korak;
		}
		korak *= 2;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	//grupna operacija koja odgovara ovome je reduce
	int rezultat;
	MPI_Reduce(&myRank, &rezultat, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myRank == 0) {
		printf("moja suma: %d\n", mojaSuma);
		printf("rezultat: %d\n", rezultat);
	}

	//b)----------------------------------------------------

	int A[n][k];
	int B[k][l];
	int C[n][l];

	int mojeKolone[k];

	if (myRank == 0) {

		printf("\nmatrica A:\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				A[i][j] = i * n + j+1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}

		printf("\nmatrica B:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < l; j++) {
				B[i][j] = i * k + j + 11;
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < np; i++) {
			MPI_Isend(&A[0][0], n * k, MPI_INT, i, 0, MPI_COMM_WORLD,&req);
		}

		//proces 0 uzima svoje kolone
		for (int j = 0; j < k; j++) {
			mojeKolone[j] = B[j][0];
		}
		

		int sendKolone[k];
		for (int i = 1; i < np; i++) {
			for (int j = 0; j < k; j++) {
				sendKolone[j] = B[j][i];
			}
			MPI_Isend(&sendKolone[0], k, MPI_INT, i, 1, MPI_COMM_WORLD, &req);
		}

		
	}
	else {
		MPI_Recv(&mojeKolone[0], k, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	MPI_Recv(&A[0][0], n * k, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	int mojMin = 99999;
	for (int i = 0; i < k; i++) {
		if (mojeKolone[i] < mojMin) {
			mojMin = mojeKolone[i];
		}
	}

	struct {
		int rank;
		int value;
	}out,in;
	in.rank = myRank;
	in.value = mojMin;
	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

	int prikazRank = out.rank;

	//------

	int mojRezultat[n];
	for (int j = 0; j < n; j++)
		mojRezultat[j] = 0;

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < k; i++) {
			mojRezultat[j] += A[j][i] * mojeKolone[i];
		}
	}

	printf("mojiRezultati proces %d:\n", myRank);
	for (int i = 0; i < n; i++) {
		printf("%d ",mojRezultat[i]);
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
		MPI_Isend(&mojRezultat[i], 1, MPI_INT, prikazRank, myRank, MPI_COMM_WORLD, &req);
	}

	//---
	if (myRank == prikazRank) {
		for (int i = 0; i < np; i++) {
			for (int j = 0; j < n; j++) {
				MPI_Recv(&C[j][i], 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}

		printf("\nmatrica C proces %d:\n",myRank);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < l; j++) {
				printf("%d ", C[i][j]);
			}
			printf("\n");
		}

	}



	MPI_Finalize();
}

//mpiexec -n 16 Jun2023.exe
#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>
 
#define brPodataka 32
//bilo koji broj podataka (stepen dvojke veci ili jednak broju procesa)

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int koraka = log2(np);
	int korak = 0;

	int mojiPodaci[brPodataka];


	if (myRank == 0) {
		int podaci[brPodataka];
		for (int i = 0; i < brPodataka; i++) {
			podaci[i] = i + 1;
		}


		for (int i = 0; i < brPodataka; i++) {
			mojiPodaci[i] = podaci[i];
		}
	}

	int stepen;
	int stepenIspod;

	while (korak < koraka) {

		stepen = (int)pow(2, koraka - korak - 1);
		stepenIspod = (int)pow(2, koraka - korak);

		if (myRank % stepen == 0) {
			if (myRank % stepenIspod == 0) {
				printf("Process %d -----> Process %d \n", myRank, myRank + stepen);
				fflush(stdout);
				MPI_Send(&mojiPodaci[stepen * (brPodataka / np)], stepen*(brPodataka/np), MPI_INT, myRank + stepen,0,MPI_COMM_WORLD);
			}
			else {
				MPI_Recv(&mojiPodaci[0], stepen * (brPodataka / np), MPI_INT, myRank - stepen, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
		}



		korak++;
	}

	printf("Process %d podataci: ", myRank);
	for (int i = 0; i < brPodataka/np; i++) {
		printf("%d ", mojiPodaci[i]);
	}
	printf("\n");

	MPI_Finalize();
}

//mpiexec -n 8 (broj procesa mora da bude stepen dvojke)
#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int koraka = sqrt(np);
	int iteracija = 0;
	int korak;

	int podatak = 45;
	int prijem;

	while (iteracija < koraka) {
		korak = pow(2, iteracija);
		if (myRank < korak) {
			MPI_Send(&podatak, 1, MPI_INT, myRank ^ korak, 33, MPI_COMM_WORLD);
			printf("P%d -> P%d\n",myRank, myRank ^ korak);
			fflush(stdout);
		}
		else if(myRank >= korak && myRank < korak*2){
			MPI_Recv(&prijem, 1, MPI_INT, myRank ^ korak, 33, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			printf("P%d primio poruku od P%d\n",myRank, myRank ^ korak);
			fflush(stdout);
		}

		MPI_Barrier(MPI_COMM_WORLD);
		if (myRank == 0) {
			printf("-------%d iteracija-------\n",iteracija);
			fflush(stdout);
		}
		MPI_Barrier(MPI_COMM_WORLD);
		iteracija++;
	}

	MPI_Finalize();
}

//mpiexec -n broj_procesa(stepen dvojke) mpi_build.exe
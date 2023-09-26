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

	int iteracija = 0;
	//koliko nivoa ima stablo
	int nivoa = log2(np);
	int korak;
	int podatak = rand();
	int prijem;

	while (iteracija < nivoa) {
		korak = pow(2, iteracija);

		if (myRank < korak) {
			MPI_Send(&podatak, 1, MPI_INT, myRank + korak, 0, MPI_COMM_WORLD);
		}
		else if (myRank >= korak && myRank < korak * 2) {
			MPI_Recv(&prijem, 1, MPI_INT, myRank - korak, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			podatak = prijem;
			printf("proces %d ---> proces %d\n", myRank - korak, myRank);
			fflush(stdout);
		}
		iteracija++;
	}
	
	MPI_Barrier(MPI_COMM_WORLD);

	printf("Proces %d: %d\n",myRank,podatak);

	MPI_Finalize();
}

//mpiexec -n (broj procesa mora da bude stepen dvojke)
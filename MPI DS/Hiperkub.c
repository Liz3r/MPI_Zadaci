#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define n 8
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int mySum = myRank;
	int sending = myRank;
	int recv;
	int iteracija = 0;
	int korak = 2;
	int trenutniProc = 0;

	while(iteracija < log2(np)) {
		if ((myRank & (int)pow(2, iteracija)) == 0) {
			MPI_Send(&mySum, 1, MPI_INT, myRank ^ (int)pow(2, iteracija), iteracija, MPI_COMM_WORLD);
		}
		else {
			MPI_Recv(&recv, 1, MPI_INT, myRank ^ (int)pow(2, iteracija), iteracija, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			mySum += recv;
		}
		MPI_Barrier(MPI_COMM_WORLD);
		iteracija++;
	}

	printf("Proces %d suma: %d\n", myRank, mySum);


	MPI_Finalize();
}

//mpiexec -n 8 Hiperkub.c
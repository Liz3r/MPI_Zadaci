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

	int* myNumbers = (int*) malloc(sizeof(int)*np);
	int mySum = 0;
	int iteracija = 0;
	myNumbers[0] = myRank;

	while (iteracija < 3) {

		//sender
		if ((int)(myRank & (int) pow(2, iteracija)) == 0) {
			int reciever = myRank ^ (int)pow(2, iteracija);
			int count = (int)pow(2, iteracija);
			MPI_Send(&myNumbers[0], count, MPI_INT, reciever, 1, MPI_COMM_WORLD);
			MPI_Recv(&myNumbers[count],count,MPI_INT,reciever,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}//reciever
		else {
			int sender = myRank ^ (int)pow(2, iteracija);
			int count = (int)pow(2, iteracija);
			MPI_Recv(&myNumbers[count], count, MPI_INT, sender, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(&myNumbers[0], count, MPI_INT, sender, 0, MPI_COMM_WORLD);
		}

		
		iteracija++;
	}


	printf("Proces %d elementi:\n", myRank);
	for (int i = 0; i < np; i++) {
		printf("%d ", myNumbers[i]);
		if (myNumbers[i] <= myRank) {
			mySum += myNumbers[i];
		}
	}
	printf("\nSuma: %d", mySum);
	printf("\n\n");

	MPI_Finalize();
}
//mpiexec -n 8 ...
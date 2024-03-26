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

	MPI_Comm cart;

	int dims[2] = { 3,3 };
	int periods[2] = { 1,1 };
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart);


	int myCoords[2];
	MPI_Cart_coords(cart, myRank, 2, myCoords);
	

	int dstCoords[2];
	int srcCoords[2];
	int srcRank, dstRank;

	MPI_Cart_shift(cart, 0, 1, &srcRank, &dstRank);
	MPI_Cart_coords(cart, srcRank, 2, srcCoords);
	MPI_Cart_coords(cart, dstRank, 2, dstCoords);

	printf("\nProces %d coords: ( %d , %d )\n", myRank, myCoords[1], myCoords[0]);
	printf("src coords: ( %d , %d )\ndst coords: ( %d , %d )\n",  srcCoords[1], srcCoords[0],dstCoords[1],dstCoords[0]);
	MPI_Finalize();
}
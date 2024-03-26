#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define m 4
#define n 6

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	MPI_Comm cart;

	int dims[2] = { m, n };
	int periods[2] = { 1, 1 };
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart);


	int myCords[2];
	MPI_Cart_coords(cart, myRank, 2, myCords);

	int myParams[3] = { myCords[0]*10 + myCords[1] * 6 + 4 / 7 , myCords[1] * 24 / 8 + myCords[0]*6+4/7 , (myCords[0] * 10 + 7) * 12 + myCords[1] * 2 + 9 / 11 };

	printf("\nProces %d coords: ( %d , %d ) | my parameters: %d %d %d\n", myRank, myCords[0], myCords[1],myParams[0], myParams[1], myParams[2]);

	MPI_Datatype sendType;
	MPI_Type_contiguous(3, MPI_INT, &sendType);
	MPI_Type_commit(&sendType);



	int src, dst;
	MPI_Cart_shift(cart,1,2,&src,&dst);

	int srcCoords[2];
	int dstCoords[2];

	MPI_Cart_coords(cart, src, 2, srcCoords);
	MPI_Cart_coords(cart, dst, 2, dstCoords);


	//printf("Proces %d src[%d %d] dst[%d %d]", myRank, srcCoords[0], srcCoords[1], dstCoords[0],dstCoords[1]);
	//printf("\nAfter||Proces %d coords: ( %d , %d ) | my parameters: %d %d %d\n", myRank, myCords[0], myCords[1], myParams[0], myParams[1], myParams[2]);
	MPI_Sendrecv_replace(myParams, 1, sendType, dst, 0, src, 0, cart, MPI_STATUS_IGNORE);

	printf("\nAfter||Proces %d coords: ( %d , %d ) | my parameters: %d %d %d\n", myRank, myCords[0], myCords[1], myParams[0], myParams[1], myParams[2]);

	MPI_Finalize();
}

//mpiexec -n 24 Kol2023.exe
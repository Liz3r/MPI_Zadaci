#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define SIZE 128


void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	/*MPI_File fajl;
	MPI_File_open(MPI_COMM_WORLD, "fajl", MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fajl);

	int buf[32];
	for (int i = 0; i < 32; i++) {
		buf[i] = i;
	}

	MPI_File_write(fajl, buf, 32, MPI_INT, MPI_STATUS_IGNORE);*/

	//citanje
	MPI_File fajl;
	MPI_File_open(MPI_COMM_WORLD, "fajl", MPI_MODE_RDONLY, MPI_INFO_NULL, &fajl);

	int mySizeInt = SIZE / sizeof(int) / np;

	int* myData = malloc(mySizeInt);
	MPI_File_read_shared(fajl, myData, mySizeInt, MPI_INT, MPI_STATUS_IGNORE);

	MPI_File_close(&fajl);

	printf("\nproces %d: ", myRank);
	for (int i = 0; i < mySizeInt; i++) {
		printf("%d ", myData[i]);
	}
	printf("\n");
	//-----------------------
	//upis
	
	MPI_Datatype upisType;
	MPI_Type_vector(2, mySizeInt / 2, np * (mySizeInt / 2), MPI_INT, &upisType);
	MPI_Type_commit(&upisType);

	MPI_File_open(MPI_COMM_WORLD, "fajl2", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fajl);
	MPI_File_set_view(fajl, (mySizeInt / 2) * myRank * sizeof(int), MPI_INT, upisType, "native", MPI_INFO_NULL);
	MPI_File_write(fajl, myData, mySizeInt, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&fajl);


	MPI_File_open(MPI_COMM_WORLD, "fajl2", MPI_MODE_RDONLY, MPI_INFO_NULL, &fajl);
	int rdbf[32];
	MPI_File_read(fajl, rdbf, 32, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&fajl);

	if (myRank == 0) {
		printf("\nFajl 2: ");
		for (int i = 0; i < 32; i++) {
			printf("%d ", rdbf[i]);
		}
		printf("\n");
	}


	MPI_Finalize();
}
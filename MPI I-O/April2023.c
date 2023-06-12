#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>


//velicina celog fajla
#define size 100

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int mySize = size / np;

	//ucitavanje

	MPI_File fajl;
	MPI_File_open(MPI_COMM_WORLD, "file1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL,&fajl);

	int* mojiElementi = malloc(mySize * sizeof(int));
	for (int i = 0; i < mySize; i++) {
		mojiElementi[i] = myRank * 100 + i + 1;
	}
	MPI_File_write_at(fajl,myRank*mySize*sizeof(int), &mojiElementi[0], mySize, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&fajl);

	//a)

	MPI_File_open(MPI_COMM_WORLD, "file2.dat", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fajl);
	MPI_File_write_shared(fajl, &mojiElementi[0], mySize, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&fajl);

	//b)

	MPI_Datatype tip;
	MPI_Type_vector(mySize, mySize / np, mySize, MPI_INT, &tip);
	MPI_Type_commit(&tip);

	MPI_File_open(MPI_COMM_WORLD, "file3.dat", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fajl);
	MPI_File_set_view(fajl, myRank*sizeof(int), MPI_INT, tip, "native", MPI_INFO_NULL);

	MPI_File_write_all(fajl, &mojiElementi[0], mySize, MPI_INT, MPI_STATUS_IGNORE);



	MPI_File_close(&fajl);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(100*sizeof(int)); //podesi velicinu
		MPI_File_read(fl, &data[0], 100, MPI_INT, MPI_STATUS_IGNORE);

		printf("\nCeo file1.dat:\n");
		for (int i = 0; i < 100; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		MPI_File_close(&fl);
	}

	MPI_File_close(&fajl);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file2.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(100 * sizeof(int)); //podesi velicinu
		MPI_File_read(fl, &data[0], 100, MPI_INT, MPI_STATUS_IGNORE);

		printf("\nCeo file2.dat:\n");
		for (int i = 0; i < 100; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		MPI_File_close(&fl);
	}

	MPI_File_close(&fajl);
	MPI_Barrier(MPI_COMM_WORLD);
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file3.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(100 * sizeof(int)); //podesi velicinu
		MPI_File_read(fl, &data[0], 100, MPI_INT, MPI_STATUS_IGNORE);

		printf("\nCeo file3.dat:\n");
		for (int i = 0; i < 100; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		MPI_File_close(&fl);
	}

	MPI_Finalize();
}
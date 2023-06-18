#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

//#define size 10*sizeof(int);
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;


	int myDataSize = (20)/np;
	int* myData = malloc(myDataSize * sizeof(int));

	//--------- upis inicijalnih vrednosti u fajl
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file1.dat", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(np * myDataSize * sizeof(int)); 
		for (int i = 0; i < np * myDataSize; i++) {
			data[i] = i + 1;
		}
		MPI_File_write_at(fl, 0, &data[0], np * myDataSize, MPI_INT, MPI_STATUS_IGNORE);
		MPI_File_close(&fl);
	}
	//citanje fajla
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(np * myDataSize * sizeof(int)); //podesi velicinu
		MPI_File_read_at(fl, 0, &data[0], np * myDataSize, MPI_INT, MPI_STATUS_IGNORE);

		printf("\nCeo fajl:  ");
		for (int i = 0; i < np * myDataSize; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		MPI_File_close(&fl);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	//--------------------------------------------------------------------------

	MPI_File fajl;
	MPI_File_open(MPI_COMM_WORLD, "file1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fajl);

	MPI_File_read_shared(fajl, &myData[0], myDataSize, MPI_INT, MPI_STATUS_IGNORE);

	printf("\nProces %d:  ", myRank);
	for (int i = 0; i < myDataSize; i++) {
		printf("%d ", myData[i]);
	}
	printf("\n");
	MPI_File_close(&fajl);

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_File_open(MPI_COMM_WORLD, "file2.dat", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fajl);

	MPI_Datatype upisType;
	MPI_Type_vector(2, myDataSize / 2, np * (myDataSize / 2), MPI_INT, &upisType);
	MPI_Type_commit(&upisType);

	MPI_File_set_view(fajl, myRank * (myDataSize / 2)*sizeof(int), MPI_INT, upisType, "native", MPI_INFO_NULL);

	MPI_File_write_all(fajl, &myData[0], myDataSize, MPI_INT, MPI_STATUS_IGNORE);

	MPI_File_close(&fajl);

	//-------------
	MPI_Barrier(MPI_COMM_WORLD);
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file2.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(np * myDataSize * sizeof(int)); //podesi velicinu
		MPI_File_read_at(fl, 0, &data[0], np * myDataSize, MPI_INT, MPI_STATUS_IGNORE);

		printf("\nCeo fajl:  ");
		for (int i = 0; i < np * myDataSize; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		MPI_File_close(&fl);
	}




	MPI_Finalize();
}
//mpiexec -n 5 Januar2022.exe
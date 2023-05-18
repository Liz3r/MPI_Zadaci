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

	MPI_File fajl;
	MPI_File_open(MPI_COMM_WORLD, "fajl", MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &fajl);

	int buf[10];

	for (int i = 0; i < 10; i++) {
		buf[i] = i + myRank * 10;
	}

	MPI_File_seek(fajl, (myRank * 10) * sizeof(int), MPI_SEEK_SET);
	MPI_File_write(fajl, buf, 10, MPI_INT, MPI_STATUS_IGNORE);

	MPI_File_close(&fajl);


	int readBuf[10];

	MPI_File fajlR;
	MPI_File_open(MPI_COMM_WORLD, "fajl", MPI_MODE_RDWR, MPI_INFO_NULL, &fajlR);

	MPI_File_seek(fajlR, myRank * 10 * sizeof(int), MPI_SEEK_SET);
	MPI_File_read(fajlR, readBuf, 10, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&fajlR);

	printf("\nProces %d:\n", myRank);
	for (int i = 0; i < 10; i++) {
		printf("%d ", readBuf[i]);
	}
	printf("\n");
	

	//

	MPI_Datatype blok;
	MPI_Type_vector(5, 2, np * 2, MPI_INT, &blok);
	MPI_Type_commit(&blok);

	MPI_File file;
	MPI_File_open(MPI_COMM_WORLD, "file2", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &file);

	MPI_File_set_view(file, myRank * 2 * sizeof(int), MPI_INT, blok, "native", MPI_INFO_NULL);

	MPI_File_write(file, readBuf, 10, MPI_INT, MPI_STATUS_IGNORE);

	MPI_File_close(&file);




	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file2", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int buff[40];
		MPI_File_read(fl, buff, 40, MPI_INT, MPI_STATUS_IGNORE);

		printf("\n");
		for (int i = 0; i < 40; i++) {
			printf("%d ", buff[i]);
		}
	}

	MPI_Finalize();
}
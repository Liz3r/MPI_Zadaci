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

	int velicina = (m * (m + 1)) / 2;
	int* mojiBrojevi = malloc(velicina * sizeof(int));

	printf("\nproces %d:\n", myRank);
	for (int i = 0; i < velicina; i++) {
		mojiBrojevi[i] = ((myRank * i + ((myRank + i)*(i+23)) % velicina)*myRank*myRank)%50;
		printf("%d ", mojiBrojevi[i]);
	}
	printf("\n");

	MPI_File fajl;
	MPI_File_open(MPI_COMM_WORLD, "file1.dat",  MPI_MODE_RDWR, MPI_INFO_NULL, &fajl);

	MPI_File_set_view(fajl, (velicina * np * sizeof(int)) - ((myRank + 1) *velicina* sizeof(int)), MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
	MPI_File_write_all(fajl, &mojiBrojevi[0], velicina, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&fajl);

	
	int* br = malloc(velicina * sizeof(int));

	MPI_File_open(MPI_COMM_WORLD, "file1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fajl);
	MPI_File_seek(fajl, (velicina * np * sizeof(int)) - ((myRank + 1) * velicina * sizeof(int)), MPI_SEEK_SET);
	MPI_File_read_all(fajl, &br[0], velicina, MPI_INT, MPI_STATUS_IGNORE);
	printf("Proces %d procitano:\n", myRank);
	for (int i = 0; i < velicina; i++) {
		printf("%d ", br[i]);
	}
	printf("\n");

	MPI_File_close(&fajl);


	//---------------------------------------------------------------------------------------------------------------
	MPI_File_open(MPI_COMM_WORLD, "file1.dat", MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fajl);

	MPI_Datatype pogledJednogProcesa;

	int count = velicina;
	int brKoraka = 0;
	while (count > 0) {
		count -= ++brKoraka;
	}
	//racuna se koliko koraka ima u velicini fajla koji se upisuje kada se upisuje 1 , 2 , 4, 8 ... (sa razmacima izmedju blokova)
	//odnosno: (blok podataka + razmak do sledeceg bloka za taj proces) = jedan korak

	int* blockLengths = malloc(brKoraka*sizeof(int));
	int* blockDisps = malloc(brKoraka * sizeof(int));

	//racunanje razmaka izmedju blokova
	for (int i = 1; i <= brKoraka; i++) {
		blockLengths[i-1] = i;
		if(i == 1)
			blockDisps[i-1] = (i-1) * np;
		else
			blockDisps[i - 1] = blockDisps[i-2] + (i - 1) * np;
		//printf("%d ", blockDisps[i-1]);
	}

	MPI_Type_indexed(brKoraka, &blockLengths[0], &blockDisps[0], MPI_INT, &pogledJednogProcesa);
	MPI_Type_commit(&pogledJednogProcesa);

	int* procitano = malloc(velicina * sizeof(int));
	MPI_File_set_view(fajl, myRank * sizeof(int), MPI_INT, pogledJednogProcesa, "native", MPI_INFO_NULL);
	MPI_File_read_all(fajl, &procitano[0], velicina, MPI_INT, MPI_STATUS_IGNORE);

	//provera datatype (da li cita ono sto bi trebalo)
	printf("Proces %d procitano izvedenim tipom:\n", myRank);
	for (int i = 0; i < velicina; i++) {
		printf("%d ", procitano[i]);
	}
	printf("\n");

	MPI_File_close(&fajl);
	MPI_Barrier(MPI_COMM_WORLD);
	//-----------------------------------------------------------------------------------------------------------------------


	//prikaz celog fajla file1.dat
	MPI_Barrier(MPI_COMM_WORLD);
	if (myRank == 0) {
		MPI_File fl;
		MPI_File_open(MPI_COMM_SELF, "file1.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &fl);

		int* data = malloc(np*velicina*sizeof(int)); //podesi velicinu
		MPI_File_read_at(fl, 0, &data[0], np * velicina, MPI_INT, MPI_STATUS_IGNORE);

		printf("\nCeo fajl:\n");
		for (int i = 0; i < np * velicina; i++) {
			printf("%d ", data[i]);
		}
		printf("\n");

		MPI_File_close(&fl);
	}
	
	MPI_Finalize();
}
//mpiexec -n 8 Oktobar2023.exe
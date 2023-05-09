#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>


#define n 8
#define m 6

//broj kolona po procesu
#define k 2

//Paralelni sistemi - Jan ll 2022  // 2. zadatak a)b)

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req,req2;
	
	int mojeKolone[k][m];
	int mojiVektorElementi[k];

	if (myRank == 0) {

		int A[m][n];
		int b[n];
		//inicijalizacija
		//A
		printf("Matrica A:\n");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = i * m + j + 11;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}

		//b
		printf("Vektor b:\n");
		for (int i = 0; i < n; i++) {
			b[i] = i + 1;
			printf("%d ", b[i]);
		}
		printf("\n");

		int koloneSlanje[k][m];
		int vektorElementiSlanje[k];
		//proces 0 uzima svoje kolone
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < m; j++) {
				mojeKolone[i][j] = A[j][(myRank % np) + (np * i)];
			}
			mojiVektorElementi[i] = b[(myRank % np) + (np*i)];
		}
		//salje ostalima
		for (int p = 1; p < np; p++) {
			for (int i = 0; i < k; i++) {
				for (int j = 0; j < m; j++) {
					koloneSlanje[i][j] = A[j][(p % np) + (np * i)];
				}
				vektorElementiSlanje[i] = b[(p % np) + (np * i)];
			}
			MPI_Isend(&koloneSlanje[0][0], k * m, MPI_INT, p, 0, MPI_COMM_WORLD, &req);
			MPI_Isend(&vektorElementiSlanje[0], k, MPI_INT, p, 1, MPI_COMM_WORLD, &req2);
		}
	}
	else {

		
		MPI_Recv(&mojeKolone[0][0], k * m, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&mojiVektorElementi[0], k , MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	}

	//racunanje rezultata
	int mojiRezultati[m];
	int suma;

	for (int i = 0; i < m; i++) {
		suma = 0;
		for (int j = 0; j < k; j++) {
			suma += mojeKolone[j][i] * mojiVektorElementi[j];
		}
		mojiRezultati[i] = suma;
	}

	//Reduce svih vrednosti u proces koji prikazuje rezultat
	int konacniRezultat[m];

	MPI_Reduce(&mojiRezultati[0], &konacniRezultat[0], m, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myRank == 0) {

		printf("Proces %d rezultat:\n", myRank);
		for (int i = 0; i < m; i++) {
			printf("%d ", konacniRezultat[i]);
		}
		printf("\n");
	}

	//-------------------- pod b)

	struct{
		int index;
		char ime[50];
		char prezime[50];
		float ocena;
	} student;
	//--komunikator
	MPI_Comm DIAG;
	MPI_Group diagGroup,worldGroup;

	int brojProcesaUDijagonali = sqrt(np);
	int* members = malloc(brojProcesaUDijagonali * sizeof(int));

	int counter = 0;
	for (int i = 0; i < np; i++) {
		if ((i % brojProcesaUDijagonali) == (i / brojProcesaUDijagonali)){
			members[counter] = i;
			counter++;
		}
	}

	MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);
	MPI_Group_incl(worldGroup, brojProcesaUDijagonali, members, &diagGroup);
	MPI_Comm_create(MPI_COMM_WORLD, diagGroup, &DIAG);

	if ((myRank % brojProcesaUDijagonali) == (myRank / brojProcesaUDijagonali)) {
		int diagRank;
		int diagSize;
		MPI_Comm_rank(DIAG, &diagRank);
		MPI_Comm_size(DIAG, &diagSize);

		//slanje
		if (diagRank == 0) {
			student.index = 1324436;
			printf("Ime:\n");
			fflush(stdout);
			scanf_s("%s", student.ime, 50);
			printf("Prezime:\n");
			fflush(stdout);
			scanf_s("%s", student.prezime, 50);
			student.ocena = 6.2;
		}
		MPI_Bcast(&student, sizeof(student), MPI_BYTE, 0, DIAG);

		printf("Proces %d, student:\nindex: %d\nime:%s\nprezime:%s\nProsecna ocena:%f\n\n", myRank, student.index, student.ime, student.prezime, student.ocena);

	}

	MPI_Finalize();
}

//mpiexec -n 4 Junll2022.exe
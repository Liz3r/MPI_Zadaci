#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define N 16
#define c 32

int ProstBroj(int broj) {

	static int b = 2;
	
	if (broj == 0 || broj == 1) {
		return 0;
	}
	if (broj == b) {
		return 1;
	}
	if (broj % b == 0) {
		return 0;
	}

	b++;

	return ProstBroj(broj);
}

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	
	int prostihBrojeva = 0;

	int prikazProc = 0;

	int s1;
	int s2;
	int mySum = 0;
	int konacnaSuma = 0;

	//petlja iz zadatka, provera sume
	if (myRank == 0) {
		int proveraSum = 0;
		for (int i = c; i < c + N; i++) {
			for (int j = N - 1; j >= 0; j--) {
				proveraSum += i + j;
			}
		}
		printf("Provera sum: %d\n", proveraSum);
	}

	for (int i = myRank; i <= myRank + N * N - np; i+= np) {

		s1 = (c + i / N);
		s2 = (N-1 - (i % N));

		mySum += s1 + s2;

		printf("P%d: %d + %d\n", myRank, s1 , s2);

		/*
		if (ProstBroj(s1)) {
			prostihBrojeva++;
		}
		if (ProstBroj(s2)) {
			prostihBrojeva++;
		}*/
	}

	//pronalazenje  najveceg
	struct {
		int val;
		int rank;
	}in,out;

	in.val = prostihBrojeva;
	in.rank = myRank;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);

	//prikazProc = out.rank;

	//konacni reduce u procesu za prikaz i prikazivanje
	MPI_Reduce(&mySum, &konacnaSuma, 1, MPI_INT, MPI_SUM, prikazProc, MPI_COMM_WORLD);

	if (myRank == prikazProc) {
		printf("Konacna suma: %d\n", konacnaSuma);
	}

	MPI_Finalize();
}

//mpiexec -n 4 mpi_build.exe
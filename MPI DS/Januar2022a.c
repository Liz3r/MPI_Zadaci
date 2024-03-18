#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define N 16

int isPrime(int n) {
	static int i = 2;

	if (n == 0 || n == 1)
		return 0;
	if (n == i)
		return 1;
	if (n % i == 0)
		return 0;

	i++;
	return isPrime(n);
}

void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	int brProstihBrojeva = 0;
	int mySum = 0;
	int currSum;
	int prikazProc;
	int ukupno;

	for (int i = myRank; i < myRank + N * N - np; i += np) {
		
		mySum += i;

		if (isPrime(i))
			brProstihBrojeva++;

	}

	struct {
		int value;
		int rank;
	}in,out;

	in.value = brProstihBrojeva;
	in.rank = myRank;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

	prikazProc = out.rank;

	MPI_Reduce(&mySum, &ukupno, 1, MPI_INT, MPI_SUM, prikazProc, MPI_COMM_WORLD);

	printf("P%d moja suma: %d\n", myRank, mySum);
	if (myRank == prikazProc) {
		printf("ukupna suma P%d: %d\n", myRank, ukupno);
	}

	MPI_Finalize();
}

//mpiexec -n 4 mpi_build.exe
#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <climits>

#define m 12
#define n 8
#define k 16
#define r 4
 
void main(int argc, char* argv[]) {
	
	int myRank, np, root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Request req;

	//-----------------------------point to point--------------------------a

	//int A[k][m];
	//int B[m][n];

	//int C[k][n];

	//int mojeVrste[r][m];
	//int mojeB[m][n];

	//int prikazRank;

	//int mojMin = 99999999;

	//int mojRezultat[r][n];

	//if (myRank == 0) {

	//	printf("Matrica A:\n");
	//	for (int i = 0; i < k; i++) {
	//		for (int j = 0; j < m; j++) {
	//			A[i][j] = i * k + j + 1;
	//			printf("%d ", A[i][j]);
	//		}
	//		printf("\n");
	//	}

	//	printf("Matrica B:\n");
	//	for (int i = 0; i < m; i++) {
	//		for (int j = 0; j < n; j++) {
	//			B[i][j] = i * k + j + 1;
	//			printf("%d ", B[i][j]);
	//		}
	//		printf("\n");
	//	}


	//	for (int i = 0; i < np; i++) {
	//		MPI_Isend(&A[i * r][0], r * m, MPI_INT, i, 0, MPI_COMM_WORLD,&req);
	//		MPI_Isend(&B[0][0], m * n, MPI_INT, i, 1, MPI_COMM_WORLD, &req);
	//	}
	//}

	//MPI_Recv(&mojeVrste[0][0], r * m, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//MPI_Recv(&mojeB[0][0],m*n,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);


	//for (int i = 0; i < r; i++) {
	//	for (int j = 0; j < m; j++) {
	//		if (mojeVrste[i][j] < mojMin)
	//			mojMin = mojeVrste[i][j];
	//	}
	//}

	//struct {
	//	int rank;
	//	int value;
	//}in,out;

	//in.rank = myRank;
	//in.value = mojMin;

	//MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

	////proces koji prikazuje
	//prikazRank = out.rank;

	//for (int i = 0; i < r; i++) {
	//	for (int j = 0; j < n; j++) {
	//		mojRezultat[i][j] = 0;
	//	}
	//}

	//for (int p = 0; p < r; p++) {
	//	for (int i = 0; i < n; i++) {
	//		for (int j = 0; j < m; j++) {
	//			mojRezultat[p][i] += mojeVrste[p][j] * mojeB[j][i];
	//		}
	//	}
	//}

	//MPI_Isend(&mojRezultat, r* n, MPI_INT, prikazRank, 5, MPI_COMM_WORLD, &req);

	//if (myRank == prikazRank) {
	//	for (int i = 0; i < np; i++) {
	//		MPI_Recv(&C[i*r][0],r*n,MPI_INT,i,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	//	}

	//	printf("Proces %d, C: \n", myRank);
	//	for (int i = 0; i < k; i++) {
	//		for (int j = 0; j < n; j++) {
	//			printf("%d ", C[i][j]);
	//		}
	//		printf("\n");
	//	}
	//}

	//-------------------------------group---------------------------------------b

	int A[k][m];
	int B[m][n];

	int C[k][n];

	int mojeVrste[r][m];
	int mojeB[m][n];

	int prikazRank;

	int mojMin = 99999999;

	int mojRezultat[r][n];

	if (myRank == 0) {

		printf("Matrica A:\n");
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < m; j++) {
				A[i][j] = i * k + j + 1;
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}

		printf("Matrica B:\n");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				mojeB[i][j] = i * k + j + 1;
				printf("%d ", mojeB[i][j]);
			}
			printf("\n");
		}


		
	}

	MPI_Scatter(&A[0][0], r * m, MPI_INT, &mojeVrste[0][0], r * m, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&mojeB[0][0], m * n, MPI_INT, 0, MPI_COMM_WORLD);


	for (int i = 0; i < r; i++) {
		for (int j = 0; j < m; j++) {
			if (mojeVrste[i][j] < mojMin)
				mojMin = mojeVrste[i][j];
		}
	}

	struct {
		int rank;
		int value;
	}in, out;

	in.rank = myRank;
	in.value = mojMin;

	MPI_Allreduce(&in, &out, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

	//proces koji prikazuje
	prikazRank = out.rank;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < n; j++) {
			mojRezultat[i][j] = 0;
		}
	}

	for (int p = 0; p < r; p++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				mojRezultat[p][i] += mojeVrste[p][j] * mojeB[j][i];
			}
		}
	}

	MPI_Gather(&mojRezultat[0][0], r* n, MPI_INT, &C[0][0], r* n, MPI_INT, prikazRank, MPI_COMM_WORLD);

	if (myRank == prikazRank) {
		printf("Proces %d, C: \n", myRank);
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", C[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
}

//mpiexec -n 4 ...
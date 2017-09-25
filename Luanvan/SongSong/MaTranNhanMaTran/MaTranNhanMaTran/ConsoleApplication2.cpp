#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define NRA 62
#define NCA 15
#define NCB 7
#define MASTER 0 
#define FROM_MASTER 1 
#define FROM_WORKER 2
int main(int argc, char** argv)
{
	int numtasks, taskid, numworkers, source, dest, mtype, rows, averow, extra, offset, i, j, k, rc;
	double a[NRA][NCA], b[NCA][NCB], c[NRA][NCB];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	if (numtasks < 2)
	{
		printf("Need at l e a s t two MPI ta s ks . Qui tt in g . . . \ n");
		MPI_Abort(MPI_COMM_WORLD,&rc);
		exit(1);
	}
	numworkers = numtasks - 1;

	//∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ master task ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ 
	if (taskid == MASTER)
	{
		printf("mpi_mm has s t a r t e d with %d tas k s . \ n", numtasks);
		printf(" I n i t i a l i z i n g a rr ays . . . \ n");
		for (i = 0; i < NRA; i++)
		{
			for (j = 0; j < NCA; j++)
			{
				a[i][j] = i + j;
				for (i = 0; i < NCA; i++)
				{
					for (j = 0; j < NCB; j++)
					{
						b[i][j] = i * j;
					}
				}
			}
		}
		// Send matrix data to the worker tasks 
		averow = NRA / numworkers;
		extra = NRA%numworkers;
		offset = 0; mtype = FROM_MASTER;
		for (dest = 1; dest <= numworkers; dest++)
		{
			rows = (dest <= extra) ? averow + 1 : averow;
			printf(" Sending %d rows to task %d o f f s e t=%d\n", rows, dest, offset);
			MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&a[offset][0], rows * NCA, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
			MPI_Send(&b, NCA * NCB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
			offset = offset + rows;
			//Receive r e s u l t s from worker t a sks
			mtype = FROM_WORKER;
			for (i = 1; i <= numworkers; i++)
			{
				source = i;
				MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
				MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
				MPI_Recv(&c[offset][0], rows * NCB, MPI_DOUBLE, source, mtype, MPI_COMM_WORLD, &status);
				printf(" Received r e s u l t s from task %d\n", source);
			}
			//Print results 
			printf(" ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ \ n");
			printf(" Res ult Matrix : \ n");
			for (i = 0; i < NRA; i++)
			{
				printf("\n");
				for (j = 0; j<NCB; j++)
					printf("%6.2 f ", c[i][j]);
			}
			printf("\n∗∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ \ n");
			printf("Done . \ n");
		}
		// ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ worker task ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ ∗ 
		if (taskid > MASTER)
		{
			// Receive matrix data from master t ask 
			mtype = FROM_MASTER;
			MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
			MPI_Recv(&a, rows * NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
			MPI_Recv(&b, NCA *NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
			// Do matrix mu ltiply
			for (k = 0; k < NCB; k++)
			for (i = 0; i < rows; i++)
			{
				c[i][k] = 0.0;
				for (j = 0; j < NCA; j++)
					c[i][k] = c[i][k] + a[i][j] * b[j][k];
			}
			//Send results back to master t ask 
			mtype = FROM_WORKER;
			MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
			MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
			MPI_Send(&c, rows * NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
		}
		MPI_Finalize();
	}
}
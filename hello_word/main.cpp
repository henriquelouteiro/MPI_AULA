#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int size, rank;

	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &size); //size -> valor de processos participantes 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("\n Eu sou o precesso %d de %d processos.", rank, size);
	MPI_Finalize();
	return  0;
}

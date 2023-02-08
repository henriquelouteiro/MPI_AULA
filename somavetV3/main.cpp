#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

void geraDados(int Vet[], const int tam);

int main(int argc, char* argv[])
{
	const int TAM = 8;
	int rank, size, r;
	int soma_p = 0, soma_tot = 0;
	MPI_Status status;

	int Vet[TAM];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	r = TAM/size;
	int A[r];

	if(rank == 0)
		geraDados(Vet, TAM);

	MPI_Scatter(&Vet, r, MPI_INT, &A, r, MPI_INT, 0, MPI_COMM_WORLD);

	for(int i = 0; i < r; i++)
		soma_p += A[i];


	MPI_Reduce(&soma_p, &soma_tot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("\nSoma: %2d", soma_tot);
	MPI_Finalize();

	return 0;
}

void geraDados(int Vet[], const int tam)
{
	srand(time(NULL));

	printf("\nValores gerados: \n\n");
    	for(int i = 0; i < tam; i++)
     	{
          	Vet[i] = rand() % 100;
		printf("%4d", Vet[i]);
     	}
}

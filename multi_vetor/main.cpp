#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <unistd.h>

#define TAMMAX 8

void gerarDados(int Vet[], int tam);

int main(int argc, char* argv[])
{
	int rank, size, i;
	int vetA[TAMMAX], vetB[TAMMAX];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int r = TAMMAX/size;
	int subA[r], subB[r];

	if(rank == 0){
		gerarDados(vetA, TAMMAX);
		sleep(5);
		gerarDados(vetB, TAMMAX);
	}

	MPI_Scatter(vetA, r, MPI_INT, subA,r,MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(vetB,r,MPI_INT,subB,r,MPI_INT, 0, MPI_COMM_WORLD);

	int soma_p = 0,soma_t=0;
	for(i=0;i<r;i++)
		soma_p += subA[i] * subB[i];

	MPI_Reduce(&soma_p, &soma_t,1,MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);
	if(rank == 0)
		printf("\nProcesso %d -- Resultado: %d.\n",rank,soma_t);	

	MPI_Finalize();
	return 0;
}

void gerarDados(int Vet[], const int tam){
	srand(time(NULL));

	printf("\nValoreres gerados: \n\n");
	for(int i = 0; i< tam; i++){
		Vet[i] = rand()%10;
	printf("%4d", Vet[i]);
	}
}

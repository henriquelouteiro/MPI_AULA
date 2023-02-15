#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

#define TAMMAX 8

void geraDados(int Vet[], const int tam);

int main(int argc, char* argv[])
{
	int rank,size,i;
	int soma=0, somaP = 0;
	int vet[TAMMAX], somaPre[TAMMAX];
	double inicio, fim;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, 	&size);
	MPI_Comm_rank(MPI_COMM_WORLD,	&rank);

	int tam = TAMMAX/size;
	int subVet[tam];
	if(rank == 0)
		geraDados(vet,TAMMAX);
	memset(somaPre,0,TAMMAX*sizeof(int));
	
	inicio = MPI_Wtime();

	MPI_Scatter(&vet,tam,MPI_INT,subVet,tam,MPI_INT,0,MPI_COMM_WORLD);
	for(i = 0;i<tam;i++)
		somaP += subVet[i];

	MPI_Scan(&somaP, &soma,1,MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	printf("\n Processo %d: soma: %2d \n",rank,soma);

	////////////////
	//calcule as somas parciais em pi
	somaPre[0] = soma - somaP + subVet[0];
	for(i=1;i<tam;i++)
		somaPre[i] = somaPre[i-1] + subVet[i];
	
	fim = MPI_Wtime();

	//imprimindo a soma parcial em pi
	for(i=0;i<tam;i++)
		printf("\n Processo %d (tempo: %.8f seg) : somaPre[%d]: %d \n",rank,fim-inicio,i,somaPre[i]);
	///////////////


	MPI_Finalize();
	return 0;
}

void geraDados(int Vet[], const int tam){
	srand(time(NULL));

	printf("\nValores Gerados: \n\n");
		for(int i=0; i <tam; i++)
			{
			Vet[i] = rand() % 10;
			printf(" %4d ",Vet[i]);
			}
}

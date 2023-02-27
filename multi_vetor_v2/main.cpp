#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <unistd.h> // sleep(tempo em seg)

#define TAMMAX 4

void geraVet(int Vet[], const int tam);
void geraMatriz(int Mat[][TAMMAX], const int tam);

int main(int argc, char* argv[])
{
    int rank, size, i, j;
    int matA[TAMMAX][TAMMAX], vet[TAMMAX];
    int R[TAMMAX];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        geraMatriz(matA, TAMMAX);
        sleep(2);
        geraVet(vet, TAMMAX);
    }

    int tam = TAMMAX/size;
    int matAux[tam][TAMMAX];
    int vetAux[tam];

    MPI_Bcast(&vet, TAMMAX, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&matA, tam*TAMMAX, MPI_INT, 
                &matAux, tam*TAMMAX, MPI_INT, 0, MPI_COMM_WORLD);
    
    memset(&vetAux, 0, sizeof(int)*tam);
    for(i = 0; i < tam; i++)
        for(j = 0; j < TAMMAX; j++)
            vetAux[i] += matAux[i][j] * vet[j];

    MPI_Gather(&vetAux, tam, MPI_INT, &R, tam, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("\nResultado:");
        for(i = 0; i < TAMMAX; i++)
            printf("\n%2d", R[i]);
    }
    MPI_Finalize();
    return 0;
}

void geraMatriz(int mat[][TAMMAX], const int tam)
{
	srand(time(NULL));

	printf("\nMatriz gerada: \n\n");
    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < tam; j++)
        {
            mat[i][j] = rand() % 10;
    	    printf("%4d", mat[i][j]);
        }
        printf("\n");
 	}
}

void geraVet(int Vet[], const int tam)
{
	srand(time(NULL));

	printf("\nVetor gerado: \n\n");
    for(int i = 0; i < tam; i++)
    {
        Vet[i] = rand() % 10;
    	printf("%4d", Vet[i]);
 	}
}

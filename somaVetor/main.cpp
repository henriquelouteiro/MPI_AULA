#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

void geraDados(int Vet[], const int tam);

int main(int argc, char *argv[])
{
    const int TAM = 128;
    int rank, size, r;
    int soma_p = 0, soma_tot = 0;
    MPI_Status status;

    int Vet[TAM];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    r = TAM / size;
    int A[r];

    if (rank == 0)
    {
        geraDados(Vet, TAM);

        for (int i = 0; i < r; i++)
        {
            A[i] = Vet[i];
            soma_p += A[i];
        }
        for (int i = 1; i < size; i++)
        {
            int k = 0;
            for (int j = i * r; j <= ((i + 1) * r) - 1; j++)
            {
                A[k] = Vet[j];
                k++;
            }
            MPI_Send(&A, r, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        soma_tot = soma_p;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&soma_p, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            soma_tot += soma_p;
        }

        printf("\nSoma total: %2d.\n", soma_tot);
    }
    else
    {
        MPI_Recv(&A, r, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int soma_p = 0;
        for (int i = 0; i < r; i++)
            soma_p += A[i];

        MPI_Send(&soma_p, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}

void geraDados(int Vet[], const int tam)
{
    srand(time(NULL));

    printf("\nValores gerados: \n\n");
    for (int i = 0; i < tam; i++)
    {
        Vet[i] = rand() % 100;
        printf("%4d", Vet[i]);
    }
}
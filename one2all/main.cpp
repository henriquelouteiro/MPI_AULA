#include <stdio.h>
#include "mpi.h"

int main()
{
	int rank, size, count;
	float data;
	MPI_Status status;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0){
		printf("\n informe o valor real: ");
		scanf("\n%f", &data);

		for(int i=1; i< size; i++){
			MPI_Send(&data,1,MPI_FLOAT,i,0, MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(&data,1,MPI_FLOAT,0,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_FLOAT, &count);

		printf("\n [processo %d]: %.2f.", rank, data);
		//printf("");
	}
	MPI_Finalize();
	return 0;

}

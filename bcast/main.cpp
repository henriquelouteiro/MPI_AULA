#include <stdio.h>
#include "mpi.h"

int main() {
	int rank,size,valor;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == 0){
		scanf("\n%d", &valor);
	}
	MPI_Bcast(&valor,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("\nprocesso %d: %d\n", rank, valor);

	MPI_Finalize();
	return 0;
}

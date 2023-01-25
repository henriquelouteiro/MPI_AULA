#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(size !=4){
		printf("está aplicacao so funciona para 4 processos, quantidade de processos %d \n",size);
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}
	
	const double waiting_time = 0.25;
	int message = 12345;
	double start;
	double end;

	if(rank == 0){
		start = MPI_Wtime();

		while(MPI_Wtime() - start < waiting_time)
		{}
		MPI_Send(&message, 1 , MPI_INT, 1, 0, MPI_COMM_WORLD);
	}else{
		MPI_Recv(&message, 1 ,MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		start = MPI_Wtime();
		
		while(MPI_Wtime() - start < waiting_time)
		{}		
		
		if(rank != size -1)
			MPI_Send(&message, 1, MPI_INT, rank +1, 0, MPI_COMM_WORLD);
	}
	
	end =  MPI_Wtime();

	printf("[P %d] gastou %.2f durante a tarefa. \n", rank,end-start);

	MPI_Finalize();

	return EXIT_SUCCESS;
}

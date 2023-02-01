#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){
	int rank,size;
	int tag,i,count;
	int buffer;

	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	tag = 2312;
	count = 1;	

	request = MPI_REQUEST_NULL;

	if(rank == 0){
		buffer = 2020;
		for(i=1;i<size;i++){
			MPI_Isend(&buffer, count, MPI_INT, i, tag, MPI_COMM_WORLD, &request);
			//MPI_Wait(&request, &status);

		}
	}
	else{
		MPI_Irecv(&buffer, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &request);
		//MPI_Wait(&request, &status);
		
	}
	
	MPI_Wait(&request, &status);

	if(rank == 0)
		printf("PROCESSADOR %d enviou %d\n", rank, buffer);
	else
		printf("PROCESSADOR %d recebeu %d\n", rank,buffer);

	MPI_Finalize();
	return 0;
}


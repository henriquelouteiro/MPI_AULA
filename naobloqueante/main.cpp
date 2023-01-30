#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){
	int rank,size;
	int tag,source,dest,count;
	int buffer;

	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	tag = 2312;
	source = 0; dest = 1;
	request = MPI_REQUEST_NULL;

	if(rank == source){
		buffer = 2020;
		MPI_Isend(&buffer, count, MPI_INT, dest, tag, MPI_COMM_WORLD, &request);
	}
	if(rank == dest){
		MPI_Irecv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &request);
	}
	
	MPI_Wait(&request, &status);
	
	if(rank == source)
		printf("PROCESSADOR %d enviou %d\n", rank, buffer);
	if(rank == dest)
		printf("PROCESSADOR %d recebeu %d\n", rank,buffer);

	MPI_Finalize();
	return 0;
}


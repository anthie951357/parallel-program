#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
int main(int argc, char* argv[]){
	int myrank, nprocs;
	
	int size = 200000000*nprocs;
	// int *ia = (int *)malloc((size_t)sizex * sizeof(int));
	int *array_send, *array_recv;
	array_send = (int *)malloc(sizeof(int) * size);
	array_recv = (int *)malloc(sizeof(int) * 200000000);
	
	double Start_time, End_time;
	
//	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	
	
	Start_time = MPI_Wtime();
	/*int MPI_Gather(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)*/
	MPI_Gather(&array_send[0], size, MPI_INT, &array_recv[0], size, MPI_INT, 0, MPI_COMM_WORLD);
	End_time = MPI_Wtime();
	
	double Total_time = End_time - Start_time;
	printf("Processor %d of %d tooks %f seconds\n", myrank, nprocs, Total_time);
	MPI_Finalize();
}


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
	
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	
	
	Start_time = MPI_Wtime();
	if(myrank == 0)
	{
		//MPI_Send (buf, count, datatype, dest, tag, communicator, ierr)
		for(int i = 1; i < nprocs; i++)
		{
			MPI_Recv(&*array_send, 200000000, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
		}
	}
	else
	{
		//MPI_Recv (buf, count, datatype, source, tag, communicator, status, ierr)
		//MPI_Recv(&array_recv[0][0],8000*8000,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		//MPI_Recv(array_recv, size, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(&*array_recv, size, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	End_time = MPI_Wtime();
	double Total_time = End_time - Start_time;
	printf("Processor %d of %d tooks %f seconds\n", myrank, nprocs, Total_time);
	MPI_Finalize();
}


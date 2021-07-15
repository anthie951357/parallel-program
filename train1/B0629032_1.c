#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
int main(int argc, char* argv[]){
	int myrank, nprocs;
	int **array_send = NULL , **array_recv = NULL;
	double Start_time , End_time ;
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	array_recv = (int **)malloc(sizeof(int *) * 8000);
	for(int i = 0; i < 8000; i++)
	{
		array_recv[i] = (int *)malloc(sizeof(int) * 8000);
	}
	
	array_send = (int **)malloc(sizeof(int *) * 8000);
	for(int i = 0; i < 8000; i++)
	{
		array_send[i] = (int *)malloc(sizeof(int) * 8000);
	}
	
	Start_time = MPI_Wtime();
	if(myrank == 0)
	{
		for(int i = 0; i < 8000; i++)
		{
			for(int j = 0; j < 8000; j++)
			{
				array_send[i][j] = 1;
			}
		}
		//MPI_Send (buf, count, datatype, dest, tag, communicator, ierr)
		for(int i = 1; i < nprocs; i++)
		{
			MPI_Send(&array_send[0][0], 8000*8000, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	else
	{
		//MPI_Recv (buf, count, datatype, source, tag, communicator, status, ierr)
		MPI_Recv(&array_recv[0][0],8000*8000,MPI_INT,0,0,MPI_COMM_WORLD,&status);
	}
	End_time = MPI_Wtime();
	double Total_time = End_time - Start_time;
	printf("Processor %d of %d tooks %f seconds\n", myrank, nprocs, Total_time);
	MPI_Finalize();
	 
}

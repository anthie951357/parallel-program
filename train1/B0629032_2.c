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
	
/*	array_recv = (int **)malloc(sizeof(int *) * 8000);
	for(int i = 0; i < 8000; i++)
	{
		array_recv[i] = (int *)malloc(sizeof(int) * 8000);
	}
*/	
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
		//int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int root, MPI_Comm comm)
		MPI_Bcast(&array_send[0][0], 8000*8000, MPI_INT, 0, MPI_COMM_WORLD);
	}
	
	End_time = MPI_Wtime();
	double Total_time = End_time - Start_time;
	printf("Processor %d of %d tooks %f seconds\n", myrank, nprocs, Total_time);
	MPI_Finalize();
	 
}

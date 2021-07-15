#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
int main(int argc, char* argv[]){
	int myrank, nprocs;
	int size = 1000000000/nprocs;
	// int *ia = (int *)malloc((size_t)sizex * sizeof(int));
	int *array_send, *array_recv;
	array_send = (int *)malloc(sizeof(int) * 1000000000);
	array_recv = (int *)malloc(sizeof(int) * size);
	
	double Start_time, End_time;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	
	
	Start_time = MPI_Wtime();
	if(myrank == 0)
	{
		for(int j = 0; j < 1000000000; j++)
		{
			array_send[j] = 1;
		}
	}
	/*int MPI_Scatter�]const void * sendbuf�Aint sendcount�AMPI_Datatype sendtype�A�L��* recvbuf�Aint recvcount�AMPI_Datatype recvtype�Aint root�AMPI_Comm comm�^
	Sendbuf
		�o�e�w�İϪ��a�}�]��ܡA�Ȧbroot�B���ġ^
�o�e�p��
�o�e��C�Ӷi�{�������ơ]��ơA�Ȧbroot�B���ġ^
�o�e����
�o�e�w�İϤ������ƾ������]�Ȧbroot�B���ġ^�]�y�`�^
����
�����w�İϤ��������ơ]��ơ^
�﫬
�����w�İϤ������ƾ������]�y�`�^
��
�o�e�i�{���š]��ơ^
�q�T
�Ǽ��̡]�y�`�^*/
	MPI_Scatter(&array_send[0], size, MPI_INT, &array_recv[0], MPI_INT, 0, MPI_COMM_WORLD);
	
	
	End_time = MPI_Wtime();
	double Total_time = End_time - Start_time;
	printf("Processor %d of %d tooks %f seconds\n", myrank, nprocs, Total_time);
	MPI_Finalize();
}


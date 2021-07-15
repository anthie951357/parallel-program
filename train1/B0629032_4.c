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
	/*int MPI_Scatter（const void * sendbuf，int sendcount，MPI_Datatype sendtype，無效* recvbuf，int recvcount，MPI_Datatype recvtype，int root，MPI_Comm comm）
	Sendbuf
		發送緩衝區的地址（選擇，僅在root處有效）
發送計數
發送到每個進程的元素數（整數，僅在root處有效）
發送類型
發送緩衝區元素的數據類型（僅在root處有效）（句柄）
收款
接收緩衝區中的元素數（整數）
改型
接收緩衝區元素的數據類型（句柄）
根
發送進程等級（整數）
通訊
傳播者（句柄）*/
	MPI_Scatter(&array_send[0], size, MPI_INT, &array_recv[0], MPI_INT, 0, MPI_COMM_WORLD);
	
	
	End_time = MPI_Wtime();
	double Total_time = End_time - Start_time;
	printf("Processor %d of %d tooks %f seconds\n", myrank, nprocs, Total_time);
	MPI_Finalize();
}


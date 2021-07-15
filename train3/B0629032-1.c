#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int happy(const void *arry, const void *arry2) {
return (*(int *) arry - *(int *) arry2);
}

int main(int argc, char *argv[]){
	int my_rank, nprocs;
	double Start_time = 0, End_time = 0;
	int bucketsize = 100000;
	
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	int **bucketArry;
	bucketArry = (int **)malloc(sizeof(int) * nprocs);
	
	int *FinalArr = malloc(sizeof(int) * 100000000);
	int *bucket_elements_num;
	bucket_elements_num = (int *) malloc(sizeof(int) * nprocs);
	for (int i = 0; i < nprocs; i++) {
		bucket_elements_num[i] = 0;
	}
	
	Start_time = MPI_Wtime();
	if(my_rank == 0){
		for(int i = 0; i < nprocs; i++){
			bucketArry[i] = (int *)malloc(sizeof(int) * bucketsize);
		}
		for(int j = 0; j < nprocs; j++){
			for(int k = 0; k < bucketsize; k++){
				bucketArry[j][k] = 0;
			}
		}
	
		int part = 100000/nprocs;//partition of bucket, such as 0~99, 100~199
		srand(time(NULL));
		int *tmp_arry = malloc(sizeof(int) * 100000000);
	
		for(int x = 0; x < 100000000; x++)
		{
			int n = rand()%100000;
			tmp_arry[x] = n;
		}
		
		for(int i = 0; i < 100000000; i++){
			for(int x = 0; x < nprocs; x++){
				if(tmp_arry[i] >= x * part && tmp_arry[i] < (x + 1) * part){
					bucketArry[x][(tmp_arry[i]%bucketsize)] = tmp_arry[i];
					bucket_elements_num[x]=bucket_elements_num[x]+1;
					break;
				}
			}
		}
	
		free(tmp_arry);
	
		/*for(int i = 0; i < nprocs; i++){
			printf("bucket contain num : %d\n", bucket_elements_num[i]);
		} */
	
		for (int i = 0; i < nprocs; i++) {
			int *Send = (int *) malloc(sizeof(int) * 100000000);
			for (int j = 0; j < 100000000; j++) {
				if (j < bucket_elements_num[i])
					Send[j] = bucketArry[i][j];
				else
					Send[j] = -1;
			}
			MPI_Send(Send, 100000000, MPI_INT, i, 0, MPI_COMM_WORLD);
			free(Send);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	
	int *Recv = (int *) malloc(sizeof(int) * 100000);
	for (int c = 0; c < nprocs; c++) {
		if (my_rank == c) {
			MPI_Recv(Recv, 100000000, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);
			int recv_Size = 0;
		for (int i = 0; i < 100000000; i++) {
			if (Recv[i] == -1){
				break;
			} 
			recv_Size++;
		}
		qsort(Recv, recv_Size, sizeof(int), happy);
	
		MPI_Send(Recv, recv_Size, MPI_INT, 0, 0, MPI_COMM_WORLD);

		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	int site = 0;
	if (my_rank == 0) {
		int *result = malloc(sizeof(int) * 100000000);
		for (int i = 0; i < 100000000; ++i) {
			result[i] = 0;
		}
		for (int i = 0; i < nprocs; i++) {
			MPI_Recv(result+site, bucket_elements_num[i], MPI_INT, i, 0, MPI_COMM_WORLD, &Status);
			site += bucket_elements_num[i];
		}

		qsort(FinalArr, 100000000, sizeof(int), cmp);
		for (int i = 0; i < 100000000; ++i) {
			if (FinalArr[i] != result[i]) {
				printf("%d %d\n", FinalArr[i], result[i]);
			}
		}
	}


	End_time = MPI_Wtime();
	float Total_time = End_time - Start_time;
	printf("processor %d tooks %f seconds\n", my_rank, Total_time);
	MPI_Finalize();
	
	return 0;
	
}


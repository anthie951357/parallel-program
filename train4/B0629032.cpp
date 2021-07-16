#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
int main() {
	srand(time(NULL));
	int* array;
	array = new int[100000000];

	int sumA = 0;
	for (int i = 0; i < 100000000; i++) {
		int tmp = rand() % 10 + 1;
		array[i] = tmp;
		//printf("%d ", array[i]);
		sumA = sumA + array[i];
	}
	//printf("%d\n", sumA);
	int answer = 0;
#pragma omp parallel num_threads(16)
	{
		double startTime = omp_get_wtime();
#pragma omp for
		for (int i = 0; i < 100000000; i++) {
#pragma omp atomic
			answer += array[i];
		}
		double endTime = omp_get_wtime();
		printf(" < T: % d > -time = % f\n", omp_get_thread_num(), (endTime - startTime));
	}
	printf("\n");
	printf("sum = %d\n", answer);

	return 0;
}

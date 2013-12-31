#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mysort.h"

int compare(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main(){
	int i = 0;
	int len = 100000;
	clock_t cost = 0;
	FILE *fp = fopen("input.txt", "r");
	int *data = (int*)malloc(sizeof(int) * len);
	for(i = 0; i < len; i++){
		fscanf(fp, "%d", &data[i]);
	}
	fclose(fp);

	cost = clock();
	myheapsort(data, len, sizeof(int), compare);
	cost = clock() - cost;

	fp = fopen("nlognout.txt", "w");
	for(i = 0; i < len; i++){
		fprintf(fp, "%d ", data[i]);
	}
	fprintf(fp, "\nAlgorithm: Heap sort\nCost time: %ld(ms)", cost * 1000 / CLOCKS_PER_SEC);
	fclose(fp);

	fp = fopen("input.txt", "r");
	for(i = 0; i < len; i++){
		fscanf(fp, "%d", &data[i]);
	}
	fclose(fp);

	cost = clock();
	mybubblesort(data, len, sizeof(int), compare);
	cost = clock() - cost;
	
	fp = fopen("n2ouput.txt", "w");
	for(i = 0; i < len; i++){
		fprintf(fp, "%d ", data[i]);
	}
	fprintf(fp, "\nAlgorithm: Bubble sort\nCost time: %ld(ms)", cost * 1000 / CLOCKS_PER_SEC);
	fclose(fp);
	
	free(data);

	return 0;
}

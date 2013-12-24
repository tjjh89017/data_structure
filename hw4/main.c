#include <stdio.h>
#include <stdlib.h>

#include "mysort.h"

int compare(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main(){
	int a[] = {1000, 100, 10, 1, 2, 20, 200, 2000};
	int len = sizeof(a) / sizeof(int);

	myheapsort(a, len, sizeof(int), compare);

	int i = 0;
	for(i = 0; i < len; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}

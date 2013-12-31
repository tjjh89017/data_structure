#ifndef __MYSORT_H__
#define __MYSORT_H__

#include <stdio.h>
#include <stdlib.h>


void myheapsort(void *array_base, int len, int size, int (*cmp)(const void*, const void*));
void mybubblesort(void *array_base, int len, int size, int (*cmp)(const void*, const void*));

#endif

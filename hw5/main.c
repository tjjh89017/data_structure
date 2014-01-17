#include <stdio.h>
#include <stdlib.h>

#include "myset.h"

typedef struct
{
	char start;
	char end;
	int weight;
}edge;

int edge_cmp(const void *a, const void *b)
{
	return ((edge*)a)->weight - ((edge*)b)->weight;
}

int hash(const void *a)
{
	return *(char*)a;
}

int cmp(const void *a, const void *b)
{
	return *(char*)a - *(char*)b;
}

int main(int argc, char *argv[]){

	char *path = "input.txt";
	if(argc > 1)
		path = argv[1];

	int weight = 0;
	char vertax[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	FILE *file = fopen(path, "r");
	int num = 0;
	fscanf(file, "Number of vectors: %d", &num);

	edge **es = (edge**)malloc(sizeof(edge*) * (num - 1) * num / 2);
	es[0] = (edge*)malloc(sizeof(edge));
	edge *e = es[0];
	int i = 0;
	// " (%c,%c)%*c[%d]" the space is a special skill to ignore invisible character
	while(fscanf(file, " (%c,%c)%*c[%d]", &e->start, &e->end, &e->weight) != EOF){
		i++;
		es[i] = (edge*)malloc(sizeof(edge));
		e = es[i];
	}
	free(e);
	int elen = i;

	qsort(es, elen, sizeof(edge*), edge_cmp);

	myset **ss = (myset**)malloc(sizeof(myset*) * num);
	for(i = 0; i < num; i++){
		ss[i] = myset_new(num, cmp, hash);
		myset_add(ss[i], &vertax[i]);
	}

	int slen = num;
	int j = 0;
	for(i = 0; i < elen; i++){
		e = es[i];
		int spos = num, epos = num;
		// find vertax in which set
		for(j = 0; j < num; j++){
			if(ss[j] == NULL)
				continue;
			if(spos >= num && myset_find(ss[j], &e->start))
				spos = j;
			if(epos >= num && myset_find(ss[j], &e->end))
				epos = j;
		}

		if(spos != epos){
			myset_add_set(ss[spos], ss[epos]);
			myset_free(ss[epos]);
			ss[epos] = NULL;
			weight += e->weight;
			slen--;
		}
	}

	if(slen == 1)
		printf("Minima Spanning Tree: %d\n", weight);
	else
		printf("No Spanning Tree\n");

	return 0;
}
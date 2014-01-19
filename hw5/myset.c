#include <stdlib.h>

#include "myset.h"

mylist* mylist_new(void *data)
{
	mylist *l = (mylist*)malloc(sizeof(mylist));
	l->data = data;
	l->next = NULL;

	return l;
}

void mylist_free(mylist *l)
{
	free(l);
}

myset* myset_new(int size, int (*cmp)(const void*, const void*), int (*hash)(const void*))
{
	myset *s = (myset*)malloc(sizeof(myset));
	s->size = size;
	s->buckets = (mylist**)malloc(sizeof(mylist*) * size);
	memset(s->buckets, 0, sizeof(mylist*) * size);
	s->cmp = cmp;
	s->hash = hash;
	s->len = 0;

	return s;
}

void myset_add(myset *s, void *data)
{
	if(!myset_find(s, data)){
		int pos = s->hash(data) % s->size;
		mylist *l = mylist_new(data);
		l->next = s->buckets[pos];
		s->buckets[pos] = l;
		s->len++;
	}
}

void myset_add_set(myset *s, myset *d)
{
	mylist *l;
	int i = 0;
	for(i = 0; i < d->size; i++){
		while(d->buckets[i]){
			l = d->buckets[i];
			myset_add(s, l->data);
			d->buckets[i] = l->next;
			mylist_free(l);
		}
	}
}

void myset_del(myset *s, void *data)
{
	int pos = s->hash(data) % s->size;
	mylist **cl = &s->buckets[pos];
	mylist *dl;

	while(*cl){
		if(s->cmp((*cl)->data, data) == 0){
			dl = *cl;
			*cl = (*cl)->next;
			mylist_free(dl);
			s->len--;
			break;
		}
		cl = &(*cl)->next;
	}
}

int myset_find(myset *s, void *data)
{
	int pos = s->hash(data) % s->size;
	mylist *cl = s->buckets[pos];

	while(cl){
		if(s->cmp(cl->data, data) == 0)
			return 1;
		cl = cl->next;
	}

	return 0;
}

int myset_length(myset *s)
{
	return s->len;
}

void myset_clear(myset *s)
{
	mylist **cl, *dl;
	int i = 0;
	for(i = 0; i < s->size; i++){
		cl = &s->buckets[i];
		while(*cl){
			dl = *cl;
			*cl = (*cl)->next;
			cl = &(*cl)->next;
			mylist_free(dl);
		}
	}
	s->len = 0;
}

void myset_free(myset *s)
{
	myset_clear(s);
	free(s->buckets);
}
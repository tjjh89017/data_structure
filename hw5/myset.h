#ifndef __MYSET_H__
#define __MYSET_H__

#include <stdlib.h>
#include <string.h>

typedef struct _list
{
	void *data;
	struct _list *next;
}mylist;

typedef struct
{
	// buckets size
	int size;
	mylist **buckets;
	// item len
	int len;
	int (*cmp)(const void*, const void*);
	int (*hash)(const void*);
}myset;

mylist* mylist_new(void *data);
void mylist_free(mylist *l);

myset* myset_new(int size, int (*cmp)(const void*, const void*), int (*hash)(const void*));
void myset_add(myset *s, void *data);
void myset_add_set(myset *s, myset *d);
void myset_del(myset *s, void *data);
int myset_find(myset *s, void *data);
int myset_length(myset *s);
void myset_clear(myset *s);
void myset_free(myset *s);

#endif
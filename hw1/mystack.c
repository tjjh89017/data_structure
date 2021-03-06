#include <stdio.h>
#include <stdlib.h>

#include "mystack.h"

static mylist* mylist_new(int size)
{
	mylist *list = malloc(sizeof(mylist));
	list->value = malloc(size * sizeof(void*));
	list->next = NULL;

	return list;
}

static int mylist_free(mylist *list)
{
	free(list->value);
	free(list);

	return 0;
}

mystack* mystack_new(int size)
{
	mystack *s = malloc(sizeof(mystack));

	s->length = 0;
	s->size = size;
	s->head = NULL;

	return s;
}

int mystack_push(mystack *s, void *val)
{
	mylist *list;
	int pos = s->length % s->size;
	if(pos == 0){
		list = mylist_new(s->size);
		list->next = s->head;
		s->head = list;
	}
	list = s->head;
	list->value[pos] = val;
	s->length++;

	return 0;
}

void* mystack_pop(mystack *s)
{
	if(s->length == 0)
		return NULL;

	s->length--;
	mylist *list = s->head;
	int pos = s->length % s->size;
	void *rtn = list->value[pos];
	list->value[pos] = NULL;

	if(pos == 0){
		s->head = list->next;
		mylist_free(list);
	}

	return rtn;
}

void* mystack_top(mystack *s)
{
	if(s->length == 0)
		return NULL;

	mylist *list = s->head;
	int pos = (s->length - 1) % s->size;

	return list->value[pos];
}

int mystack_empty(mystack *s)
{
	return s->length == 0;
}

int mystack_flush(mystack *s)
{
	mylist *list;
	while(s->head != NULL){
		list = s->head;
		s->head = s->head->next;
		mylist_free(list);
	}

	return 0;
}

int mystack_free(mystack *s)
{
	mystack_flush(s);
	free(s);

	return 0;
}

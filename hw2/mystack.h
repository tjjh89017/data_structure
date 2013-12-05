#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#define MYSTACK_DEFAULT 10

typedef struct _list{
	void **value;
	struct _list *next;
} mylist;

typedef struct{
	int length;
	int size;
	
	mylist *head;
} mystack;

mystack* mystack_new(int size);
int mystack_push(mystack *s, void *val);
void* mystack_pop(mystack *s);
void* mystack_top(mystack *s);
int mystack_empty(mystack *s);
int mystack_flush(mystack *s);
int mystack_free(mystack *s);

#endif

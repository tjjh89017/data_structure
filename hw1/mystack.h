#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#define DEFAULT_SIZE 10

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
int mystack_del(mystack *s);
int mystack_push(mystack *s, void *val);
void* mystack_pop(mystack *s);
void* mystack_top(mystack *s);
int mystack_empty(mystack *s);

#endif

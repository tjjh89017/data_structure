#ifndef __MYBTREE_H__
#define __MYBTREE_H__

typedef struct _mybtree{

	void *value;
	struct _mybtree *left;
	struct _mybtree *right;
}mybtree;

mybtree* mybtree_new(void *value);
int mybtree_free(mybtree *root);

#endif

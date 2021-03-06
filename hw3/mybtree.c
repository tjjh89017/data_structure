#include <stdio.h>
#include <stdlib.h>
#include "mybtree.h"

mybtree* mybtree_new(void *value)
{
	mybtree *tree = (mybtree*)malloc(sizeof(mybtree));
	tree->value = value;
	tree->left = tree->right = NULL;

	return tree;
}

int mybtree_free(mybtree *root)
{
	if(root == NULL)
		return 0;
	mybtree_free(root->left);
	mybtree_free(root->right);

	return 0;
}

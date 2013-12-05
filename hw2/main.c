#include <stdio.h>
#include <stdlib.h>

#include "mybtree.h"
#include "mystack.h"

#define MAX_SIZE 30

mybtree* create_from_array(char *array, int index, int len);
void inorder_travel(mybtree *root);
void inorder_travel_stack(mybtree *root);

int main(int argc, char* argv[]){

	if(argc <= 1){
		printf("Missing param\n");
		return 1;
	}

	char input[MAX_SIZE];
	int i = 0;
	FILE *file = fopen(argv[1], "r");
	fscanf(file, "%c", &input[i]);
	while(fscanf(file, " %c", &input[i]) != EOF){
		i++;
	}
	int len = i;
	mybtree *root = create_from_array(input, 0, len);

	printf("recursive: ");
	inorder_travel(root);
	printf("\n");

	printf("non-recursive: ");
	inorder_travel_stack(root);
	printf("\n");

	return 0;
}

mybtree* create_from_array(char *array, int index, int len)
{
	if(index >= len || array[index] == '-')
		return NULL;
	mybtree *root = mybtree_new(&array[index]);
	root->left = create_from_array(array, 2 * index + 1, len);
	root->right = create_from_array(array, 2 * index + 2, len);

	return root;
}

void inorder_travel(mybtree *root)
{
	if(root != NULL){
		inorder_travel(root->left);
		printf("%c", *(char*)(root->value));
		inorder_travel(root->right);
	}
}

void inorder_travel_stack(mybtree *root)
{
	mybtree *current = root;
	mystack *s = mystack_new(MYSTACK_DEFAULT);
	while(current != NULL || !mystack_empty(s)){
		if(current != NULL){
			mystack_push(s, current);
			current = current->left;
		}
		else{
			current = (mybtree*)mystack_pop(s);
			printf("%c", *(char*)(current->value));
			current = current->right;
		}
	}
	mystack_free(s);
}

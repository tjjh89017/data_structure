#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "mybtree.h"

#define SWAP(a, b, temp) \
{ \
	temp = a; \
	a = b; \
	b = temp; \
}

typedef struct{
	void *symbol;
	int weight;
}frequency;

int compare(void *a, void *b);
mybtree* huffman_tree(frequency **f, int len, int (*compare_fun)(void*, void*));
char* huffman_encode(mybtree *huff, char *s, int len);
int search_symbol(mybtree *huff, char c, char *s);

int main(){

	char s[1000];
	int len = 0;
	printf("input how many symbol\n");
	scanf("%d", &len);
	char *sym = (char*)malloc((len + 1) * sizeof(char));
	frequency **f = (frequency**)malloc(len * sizeof(frequency*));

	int i = 0, j = 0;
	for(i = 0; i < len; i++){
		f[i] = (frequency*)malloc(sizeof(frequency));
		scanf("%s %d", &sym[i], &f[i]->weight);
		f[i]->symbol = &sym[i];
	}
	printf("input the string need to encode\n");
	scanf("%s", s);
	int slen = strlen(s);

	mybtree *huffman = huffman_tree(f, len, compare);
	
	char **table = (char**)malloc(len * sizeof(char*));
	int l = log2(len) + 2;
	for(i = 0; i < len; i++){
		table[i] = (char*)malloc(l * sizeof(char));
		search_symbol(huffman, sym[i], table[i]);
		printf("%c: %s\n", sym[i], table[i]);
	}

	char *encode = (char*)malloc(l * slen * sizeof(char));
	char *ptr = encode;
	for(i = 0; i < slen; i++){
		// search symbol
		for(j = 0; j < len; j++){
			if(s[i] == sym[j]){
				ptr += sprintf(ptr, table[j]);
				break;
			}
		}
	}

	printf("%s: %s\n", s, encode);
	return 0;
}

int compare(void *a, void *b)
{
	return (((frequency*)a)->weight - ((frequency*)b)->weight);
}

mybtree* huffman_tree(frequency **f, int len, int (*compare_fun)(void*, void*))
{
	// let f be a min heap
	int i = 0;
	mybtree **heap = (mybtree**)malloc(len * sizeof(mybtree*));
	for(i = 0; i < len; i++)
		heap[i] = mybtree_new(f[i]);

	int son = 0;
	int parent = 0;
	mybtree *temp;
	for(i = 0; i < len; i++){
		son = i;
		parent = (son - 1) / 2;
		while(parent >= 0 && compare_fun(heap[son]->value, heap[parent]->value) < 0){
			SWAP(heap[son], heap[parent], temp);
			son = parent;
			parent = (son - 1) / 2;
		}
	}

	// get min 2 value and create a tree
	// left 0, right 1, and right smaller than left
	mybtree *root = heap[0];
	frequency *fre;
	son = 1;
	parent = 0;
	while(len > 1){
		fre = (frequency*)malloc(sizeof(frequency));
		fre->symbol = NULL;
		fre->weight = 0;
		root = mybtree_new(fre);

		for(i = 0; i < 2; i++){
			SWAP(heap[0], heap[len - 1], temp);
			len--;
			if(i == 0)
				root->right = heap[len];
			else
				root->left = heap[len];
			fre->weight += ((frequency*)heap[len]->value)->weight;

			// re-heap
			parent = 0;
			son = parent * 2 + 1;
			while(son < len){
				if(son < len - 1 && compare_fun(heap[son]->value, heap[son + 1]->value) > 0)
					son++;
				if(compare_fun(heap[parent]->value, heap[son]->value) < 0)
					break;
				SWAP(heap[parent], heap[son], temp);
				parent = son;
				son = parent * 2 + 1;
			}
		}

		heap[len] = root;
		len++;
		son = len - 1;
		parent = (son - 1) / 2;
		while(parent >= 0 && compare_fun(heap[son]->value, heap[parent]->value) < 0){
			SWAP(heap[son], heap[parent], temp);
			son = parent;
			parent = (son - 1) / 2;
		}
	}
	root = heap[0];
	free(heap);

	return root;
}

int search_symbol(mybtree *huff, char c, char *s)
{
	if(huff == NULL)
		return 0;

	frequency *f = huff->value;
	if(f->symbol == NULL){
		if(search_symbol(huff->left, c, s + 1))
			*s = '0';
		else if(search_symbol(huff->right, c, s + 1))
			*s = '1';
		else
			return 0;

		return 1;
	}
	
	char val = *(char*)f->symbol;
	*s = '\0';
	return (val == c);
}

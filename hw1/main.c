#include <stdio.h>
#include <stdlib.h>

#include "mystack.h"

int main(){

	mystack *s = mystack_new(DEFAULT_SIZE);
	int i = 0;
	for(i = 0; i < 100; i++)
		mystack_push(s, i);

	for(i = 0; i < 20; i++)
		mystack_pop(s);

	int out;
	while(!mystack_empty(s)){
		out = mystack_pop(s);
		printf("%d\n", out);
	}

	if(mystack_pop(s) == NULL)
		printf("true\n");

	return 0;
}

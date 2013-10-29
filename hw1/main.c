#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystack.h"
#define MAX_SIZE 100

char* infix_to_posfix(char *expr);
int combine_rule(char a, char b);
int priority(char a);

int main(){

	char expr[MAX_SIZE];
	scanf("%s", expr);

	char *postfix = infix_to_posfix(expr);
	printf("%s\n", postfix);

	return 0;
}

char* infix_to_posfix(char *expr)
{
	int len = strlen(expr);
	char *postfix = (char*)malloc(sizeof(char) * len);
	mystack *s = mystack_new(MYSTACK_DEFAULT);

	int i = 0;
	char *ptr = postfix;
	for(i = 0; i < len; i++){
		/* push '(' whatever */
		if(expr[i] == '(')
			mystack_push(s, &expr[i]);
		/* pop until the top is '(' */
		else if(expr[i] == ')'){
			while(!mystack_empty(s) && *(char*)mystack_top(s) != '('){
				*ptr = *(char*)mystack_pop(s);
				ptr++;
			}
			mystack_pop(s);
		}
		/* for this case's operand */
		else if('0' <= expr[i] && expr[i] <= '9'){
			*ptr = expr[i];
			ptr++;
		}
		/* for this case's operator */
		else{
			while(!mystack_empty(s) && combine_rule(*(char*)mystack_top(s), expr[i])){
				*ptr = *(char*)mystack_pop(s);
				ptr++;
			}
			mystack_push(s, &expr[i]);
		}
	}
	/* pop all of them */
	while(!mystack_empty(s)){
		*ptr = *(char*)mystack_pop(s);
		ptr++;
	}

	return postfix;
}

int combine_rule(char a, char b)
{
	switch(a){
		/* left combine */
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return priority(a) >= priority(b);

		/* right combine */
		case '^':
			return priority(a) > priority(b);
	}
}

int priority(char a)
{
	switch(a){
		case '*':
		case '/':
			return 3;

		case '+':
		case '-':
			return 2;

		case '(':
			return 0;
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystack.h"
#define MAX_SIZE 100

char* infix_to_posfix(char *expr);
int combine_rule(char a, char b);
int priority(char a);
int eval_operator(int a, int b, int op);
int eval_posfix(char *expr);

int main(){

	char expr[MAX_SIZE];
	scanf("%s", expr);

	char *postfix = infix_to_posfix(expr);
	printf("%s\n", postfix);
	printf("ans:%d\n", eval_posfix(postfix));

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

	mystack_free(s);
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

int eval_operator(int a, int b, int op)
{
	switch(op){
		case '*':
			return a * b;
		case '/':
			return a / b;
		case '+':
			return a + b;
		case '-':
			return a - b;
	}
}

int eval_posfix(char *expr)
{
	int ans = 0;
	int len = strlen(expr);
	mystack *s = mystack_new(MYSTACK_DEFAULT);

	int i = 0;
	for(i = 0; i < len; i++){
		/* operand push them */
		if('0' <= expr[i] && expr[i] <= '9')
			mystack_push(s, expr[i] - '0');
		/* operand pop two operand and eval them */
		else{
			/* I think I should check if stack has two elemnets */
			int b = mystack_pop(s);
			int a = mystack_pop(s);
			mystack_push(s, eval_operator(a, b, expr[i]));
		}
	}
	ans = mystack_pop(s);
	mystack_free(s);

	return ans;
}
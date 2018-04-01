#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
		int* key;
		int top;
		int max_stack_size;
}Stack;

Stack* CreateStack(int max) {
		Stack* S = NULL;
		S = (Stack*)malloc(sizeof(max));
		S->key = (int*)malloc(sizeof(int)*max);
		S -> max_stack_size = max;
		S-> top = -1;
		return S;
}

int IsFull(Stack *S) {
		if(S->top == S-> max_stack_size) return 1;
		else return 0;
}

void Push(Stack* S, int X) {
		S->top++;
		S->key[S->top] = X;
}

int IsEmpty(Stack *S) {
		if(S->top == -1) return 1;
		else return 0;
}

int Pop(Stack *S) {
		S->key[S->top] = ' ';
		S->top--;
		return S->top;
}

void DeleteStack(Stack* S) {
		free(S);
}

int main(int argc, char* argv[]) {
		FILE* fi = fopen(argv[1],"r");
		Stack* stack;
		char input_str[101];
		int max, i=0, a, b, result;

		fgets(input_str, 101, fi);
		max = strlen(input_str);
		stack = CreateStack(max);
		printf("Top numbers : ");
		while(input_str[i] != '#') {
				if('0' <= input_str[i] && input_str[i] <= '9') {
						Push(stack, input_str[i] - '0');
				}

				else if(input_str[i] == '+') {
						result = stack->key[stack->top-1] + stack->key[stack->top];
						Pop(stack);
						Pop(stack);
						Push(stack, result);
				}	else if(input_str[i] == '-') {
						result = stack->key[stack->top-1] - stack->key[stack->top];
						Pop(stack);
						Pop(stack);
						Push(stack, result);
				}	else if(input_str[i] == '*') {
						result = stack->key[stack->top-1] * stack->key[stack->top];
						Pop(stack);
						Pop(stack);
						Push(stack, result);
				}	else if(input_str[i] == '%') {
						result = stack->key[stack->top-1] % stack->key[stack->top];
						Pop(stack);
						Pop(stack);
						Push(stack, result);
				}	else if(input_str[i] == '/') {
						result = stack->key[stack->top-1] / stack->key[stack->top];
						Pop(stack);
						Pop(stack);
						Push(stack, result);
				}
				i++;
				printf("%d ",stack->key[stack->top]);
		}
		printf("\nevaluation result: ");
		printf("%d\n", stack->key[stack->top]);
}

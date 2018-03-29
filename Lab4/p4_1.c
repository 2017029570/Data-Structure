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
		S->max_stack_size = max;
		S->top = -1;
		return S;
}

int IsFull(Stack *S) {
		if(S->top == S->max_stack_size) return 1;
		else return 0;

}
void Push(Stack* S, int X) {
		S->top++;
		*(S->key) = X;

}
		

int main(int argc, char* argv[]) {
		FILE* fi = fopen(argv[1],"r");

		Stack* stack;
		char input_str[101];
		int max, i=0, a, b, result;

		fgets(input_str, 101, fi);
		max = strlen(input_str);
		printf("Pushed numbers :");
		stack = CreateStack(max);
		while(input_str[i] != '#') {
				if('0'<=input_str[i]&&input_str[i]<='9') {
						//if(IsFull(stack)) printf("Stack is full\n");
						Push(stack, input_str[i]-'0');
						printf("%d is inserted.\n",input_str[i]-'0');
						i++;
				}
				
		}
}
		

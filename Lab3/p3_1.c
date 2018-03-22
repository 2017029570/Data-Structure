#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNod;
typedef PtrToNod List;
typedef PtrToNod Position;
typedef int ElementType;
struct Node {
		ElementType element;
		Position next;
};

List MakeEmpty(List L) {
		L = (List)malloc(sizeof(struct Node));
		L->element = NULL;
		L->next = NULL;
		return L;
}

int IsEmpty(List L) {
		if(L->next == NULL) return 1;
		else return 0;
}

int IsLast(Position P, List L) {
		if(P->next == NULL) return 1;
		else return 0;
}

void Insert(ElementType X, List L, Position P) {
		Position PP;
		PP = malloc(sizeof(struct Node));
		PP->element = X;
		PP->next = P->next;
		P->next = PP;
}

void PrintList(List L) {
		L = L->next;
		for(;L;L=L->next) {
				printf("key: %d\n",L->element);
		}
}

void DeleteList(List L) {
		Position P, Tmp;
		P = L->next;
		L->next = NULL;
		while(P!=NULL) {
				Tmp = P->next;
				free(P);
				P = Tmp;
		}
}

int main(int argc, char *argv[]) {
		char command;
		int key1, key2;
		FILE *input;
		Position header = NULL;
		Position tmp = NULL;
		if(argc == 1) input = fopen("input.txt", "r");
		else input = fopen(argv[1], "r");
		header = MakeEmpty(header);
		while(1) {
				command = fgetc(input);
				if(feof(input)) break;
				switch(command) {
						case 'i':
								fscanf(input, "%d %d", &key1, &key2);
								Insert(key1, header, header);
								break;
						
						case 'p':
								PrintList(header);
								break;
						default:
								break;
				}
		}
				DeleteList(header);
				fclose(input);
				return 0;
}

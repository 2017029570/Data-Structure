#include <stdlib.h>
#include <stdio.h>
typedef struct Node *PtrToNod;
typedef PtrToNod List;
typedef PtrToNod Position;
typedef int ElementType;
struct Node
{
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
			Position Tmpcell;
			Tmpcell = malloc(sizeof(struct Node));
			Tmpcell->element = X;
			Tmpcell->next = P->next; 
			P->next = Tmpcell;
}
void PrintList(List L) {
		L = L->next;
		for(;L;L=L->next) {
				printf("key: %d\n",L->element);

		}
}
Position FindPrevious(ElementType X, List L) { 
		Position P;
		P=L;
		while(P->next != NULL && P->next->element != X)
				P = P->next;
		return P;
}

void Delete(ElementType X, List L) { 
		Position P, TmpCell;
		P=FindPrevious(X, L);
		if(!IsLast(P,L)) {
				TmpCell = P->next;
				P->next = TmpCell->next;
				free(TmpCell);
		}
}


Position Find(ElementType X, List L) {
		Position P;
		P=L->next;
		while(P!=NULL && P-> element!=X) P=P->next;
		return P;
}
void DeleteList(List L) { 
		Position P,Tmp;
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
								printf("%d %d\n",key1, key2);
								if(Find(key1, header) != NULL) {
										printf("There already is an element with key %d. Insertion failed\n", key1);
										break;
								
								}
								else if(Find(key1, header) == NULL && key1 != -1) printf("Insertion(%d) Failed : cannot find the location to be inserted.\n",key1);
								else {
									if(key2 == -1) Insert(key1,header,header);
									else {
										Insert(key1, header,Find(key2, header));
									}
								break;
								}
						case 'd':
								fscanf(input, "%d", &key1);
								Delete(key1, header);
								break;
						case 'f':
								fscanf(input, "%d", &key1);
								tmp = FindPrevious(key1, header);
								if(IsLast(tmp, header))
										printf("Could not find %d in the list\n", key1);
								else {
										if(tmp -> element>0)
												printf("Dey of the previos node of %d is %d.\n", key1, tmp->element);
										else printf("Dey of the previos node of %d is header.\n", key1);
								}
								break;
						case 'p':
								PrintList(header);
								break;
						default:
								break;
				}
		}
		system("PAUSE");
		DeleteList(header);
		fclose(input);
		return 0;
}

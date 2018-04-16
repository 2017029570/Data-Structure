#include <stdio.h>
#include <stdlib.h>
#define Max(a, b) ((a>b) ? (a) : (b))

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef struct AVLNode Position;

struct AVLNode {
		ElementType Element;
		AVLTree Left;
		AVLTree Right;
		int Height;
};
int Height(AVLTree T) {
		if(T == NULL) return -1;
		else return T->Height;
}
AVLTree Insert(ElementType X, AVLTree T) {
		if(T == NULL) {
				T = malloc(sizeof(struct AVLNode));
				if(T!=NULL) {
				T->Element = X;
				T->Height = 0;
				T->Left = T->Right = NULL;
				}
		}
		else if(X < T->Element) {
				T->Left = Insert(X, T->Left);
		}
		else if(X > T->Element) {
				T->Right = Insert(X, T->Right);
		}
		else printf("Insertion Error : There is already %d in the tree.\n", X);
//		printf("Max : %d\n", Max(Height(T->Left), Height(T->Right))); 
		T->Height = Max(Height(T->Left), Height(T->Right))+1;
//		printf("%d's Height : %d\n", T->Element, T->Height);
		return T;
}

void printInorder(AVLTree T) {
		if(T != NULL) {
				printInorder(T -> Left);
				printf("%d(%d) ",T->Element,T->Height);
				printInorder(T->Right);
		}
}

void DeleteTree(AVLTree T) {
		free(T);
}

/*Position SingleRotateWithLeft(Position node);

Position SingleRotateWithRight(Position node);

Position DoubleRotateWithLeft(Position node);

Position DoubleRotateWithRight(Position node);
*/
int main(int argc, char *argv[]) {
     	FILE *fp = fopen(argv[1], "r");		
		AVLTree myTree=NULL;
		int num;

		if(fp == NULL) {
				printf("There is no file : %s\n", argv[1]);
				exit(-1);
		}

		while(fscanf(fp, "%d", &num) != EOF) {
				myTree = Insert(num, myTree);
				printInorder(myTree);
				printf("\n");
		}

		DeleteTree(myTree);
		return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define Max(a, b) ((a>b) ? (a) : (b))

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef struct AVLNode *Position;

struct AVLNode {
		ElementType Element;
		AVLTree Left;
		AVLTree Right;
		int Height;
};

int Height(AVLTree T) {
		if(T==NULL) return -1;
		else return T->Height;
}

Position SingleRotateWithLeft(Position node) {
		Position node2;

		node2 = node->Left;
		node->Left = node2->Right;
		node2->Right = node;

		node->Height = Max(Height(node->Left), Height(node->Right)) +1;
		node2->Height = Max(Height(node2->Left), node->Height) + 1;

		return node2;
}

Position SingleRotateWithRight(Position node) {
		Position node2;

		node2 = node->Right;
		node->Right = node2->Left;
		node2->Left = node;

		node->Height = Max(Height(node->Right), Height(node->Left)) + 1;
		node2->Height = Max(Height(node2->Right), node->Height) + 1;

		return node2;
}

Position DoubleRotateWithLeft(Position node) {
		node->Left = SingleRotateWithRight(node->Left);

		return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node) {
		node->Right = SingleRotateWithLeft(node->Right);

		return SingleRotateWithRight(node);
}
AVLTree Insert(ElementType X, AVLTree T) {
		if(T == NULL) {
				T = malloc(sizeof(struct AVLNode));
				if(T != NULL) {
						T->Element = X;
						T->Height=0;
						T->Left = T->Right = NULL;
				}

		}
		else if(X < T->Element) {
				T->Left = Insert(X, T->Left);
				if(Height(T->Left) - Height(T->Right) == 2)
						if(X<T->Left->Element)
								T = SingleRotateWithLeft(T);
						else 
								T = DoubleRotateWithLeft(T);
		}
		else if(X>T->Element) {
				T->Right = Insert(X, T->Right);
				if(Height(T->Right) - Height(T->Left) == 2) {
						if(X>T->Right->Element)
								T = SingleRotateWithRight(T);
						else 
								T = DoubleRotateWithRight(T);
				}
		}
		else printf("[Error] %d already in the tree!\n", T->Element);
		T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
		return T;
}


void PrintInorder(AVLTree T) {
		if (T != NULL) {
				PrintInorder(T->Left);
				printf("%d(%d) ", T->Element, T->Height);
				PrintInorder(T->Right);
		}
}

void DeleteTree(AVLTree T) {
		free(T);
}

int main(int argc, char **argv) {
		FILE *fp = fopen(argv[1], "r");
		AVLTree myTree = NULL;
		int num;

		if(fp == NULL) {
				printf("There is no file : %s\n", argv[1]);
				exit(-1);
		}

		while(fscanf(fp, "%d", &num) != EOF) {
				myTree = Insert(num, myTree);
				PrintInorder(myTree);
				printf("\n");
		}

		DeleteTree(myTree);
		return 0;
}

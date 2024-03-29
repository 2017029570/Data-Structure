#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
		int value;
		struct Tree* left;
		struct Tree* right;
}Tree;

Tree* insertNode(Tree *root, int key) {
		if(root == NULL) {
				root = malloc(sizeof(Tree));
				root->value = key;
				root->left = NULL;
				root->right = NULL;
				printf("insert %d\n",key);
		}
		else if(key<root->value) {
				root->left = insertNode(root->left, key);
		}
		else if(key>root->value) {
				root->right = insertNode(root->right,key);
		}
		else printf("Insertion Error : There is already %d in the tree.\n",key);
		return root;
}

void printInorder(Tree* root) {
		if(root != NULL) {
				printInorder(root->left);
				printf("%d ",root->value);
				printInorder(root->right);
		}
}

void deleteTree(Tree* root) {
		if(root == NULL) return;
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
}

void main(int argc, char* argv[]) {
		FILE *fi = fopen(argv[1], "r");
		char cv;
		int key;

		Tree* root = NULL;

		while(!feof(fi)) {
				fscanf(fi, "%c", &cv);
				switch(cv) {
						case 'i':
								fscanf(fi,"%d", &key);
								root = insertNode(root, key);
								break;

						case 'p':
								fscanf(fi, "%c", &cv);
								if(cv == 'i') printInorder(root);
								printf("\n");
								break;
				}
		}
		deleteTree(root);
}


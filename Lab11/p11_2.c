#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue {
		int* key;
		int first;
		int rear;
		int qsize;
		int max_queue_size;
};


struct _Graph {
		int size;
		int* node;
		int** matrix;
};

Graph CreateGraph(int* nodes, int x) {
		Graph g = malloc(sizeof(Graph));
		g->size = x;
		g->node = (int*)malloc(sizeof(int)*(g->size));
		for(int i=0;i<g->size;i++) g->node[i] = nodes[i];
		g->matrix = (int**)malloc((sizeof(int*) * (g->size)));
		for(int i=0;i<g->size;i++) {
				g->matrix[i] = (int*)malloc((sizeof(int)*(g->size)));
				for(int j=0;j<g->size;j++) {
						g->matrix[i][j]=0;
				}
		}
		return g;
}

void InsertEdge(Graph G, int a, int b) {
		int x,y;
		for(int i=0;i<G->size;i++) {
				if(G->node[i] == a) x=i;
				else if(G->node[i]==b) y=i;
		}
		G->matrix[x][y] = 1;
}

void DeleteGraph(Graph G) {
		free(G);
}

Queue MakeNewQueue(int X) {
		Queue q = malloc(sizeof(Queue));
		q->key = (int*)malloc(sizeof(int)*X);
		q->first = q->qsize = 0;
		q->rear = -1;
		q->max_queue_size = X;

		return q;
}

int IsEmpty(Queue Q) {
		if(Q->qsize == 0) return 1;
		else return 0;
}

int IsFull(Queue Q) {
		if(Q->qsize == Q->max_queue_size) return 1;
		else return 0;
}

void Enqueue(Queue Q, int X) {
		if(IsFull(Q)) printf("Queue is full.\n");
		Q->key[++Q->rear] = X;
		Q->qsize++;
}

int Dequeue(Queue Q) {
		if(IsEmpty(Q)) printf("Queue is empty.\n");
		int a = Q->key[Q->first];
		Q->first++;
		Q->qsize--;

		return a;
}

void MakeEmpty(Queue Q) {
		Q->first = 0;
		Q->rear = -1;
}

void DeleteQueue(Queue Q) {
		free(Q);
}

void TopSort(Graph G) {
		int i,j,ch2;
		int* ch = (int*)malloc(sizeof(int)*(G->size));
		for(int v=0;v<G->size;v++) ch[v] = 0;
		Queue q = MakeNewQueue(G->size);

		ch2 = 0;

		while(ch2 < G->size) {
				if(q->qsize>=1) {
						for(int k=0;k<G->size;k++) {
								if(G->node[k] == q->key[q->first]) {
										for(int m=0;m<G->size;m++)
												if(G->matrix[k][m]!=0)
													G->matrix[k][m]--;
										break;
								}
						}
						printf("%d ",Dequeue(q));
						ch2++;
				}

			for(j=0;j<G->size;j++) {
				int ch1 = 0;
				if(ch[j] == 1);
				else {
					for(i=0;i<G->size;i++) {
							if(G->matrix[i][j] == 0) ch1++;
							else break;
					}
					if(ch1 == G->size) {
							Enqueue(q,G->node[j]);
							ch[j] = 1;
					}

				}
		
			}
					
	    }
		printf("\n");
}
int main(int argc, char* argv[]) {
		FILE *fi = fopen(argv[1], "r");
		Graph graph;
		char str[255]; int i=0;
		char *token;
		char c[3];
		int n[1000];
		fgets(str, 255, fi);
		token = strtok(str, " ");
		while(token != NULL) {
				n[i] = token[0]-'0';
				token = strtok(NULL," ");
				i++;
		}

		graph = CreateGraph(n,i);

		while(fscanf(fi,"%s",c) != EOF) {
				InsertEdge(graph, c[0]-'0',c[2]-'0');
		}

		TopSort(graph);

		return 0;
}
	

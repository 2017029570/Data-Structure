#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Graph {
		int size;
		int* node;
		int **matrix;
};

struct _Queue {
		int* key;
		int first;
		int rear;
		int qsize;
		int max_queue_size;
};

Graph CreateGraph(int* nodes,int x) {
		Graph g = malloc(sizeof(Graph));
		g->size = x;
		g->node = (int*)malloc(sizeof(int)*(g->size));
		for(int i=0;i<g->size;i++) g->node[i] = nodes[i];
		g->matrix = (int**)malloc((sizeof(int*) * (g->size)));
		for(int i=0;i<g->size;i++) {
				g->matrix[i] = (int*)malloc((sizeof(int)*(g->size)));
				for(int j=0;j<g->size;j++) {
						g->matrix[i][j] = 0;
				}
		}
		return g;
}

void InsertEdge(Graph G, int a, int b) {
		int x,y;
		for(int i=0;i<G->size;i++) {
					if(G->node[i]==a) x=i;
					else if(G->node[i]==b) y=i;
		}
		G->matrix[x][y] = 1;
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
				InsertEdge(graph, c[0]-'0', c[2]-'0');
		}
		printf("  ");
		for(int i=0;i<graph->size;i++) printf("%d ",n[i]);
		printf("\n");
		for(int i=0;i<graph->size;i++) {
				printf("%d ",n[i-1]);
				for(int j=0;j<graph->size;j++)  printf("%d ",graph->matrix[i][j]);
				printf("\n");
		}

		return 0;
}




/*Queue MakeNewQueue(int X) {
		Queue q = (Queue)malloc(sizeof(_Queue));

		q->key = NULL;
		q->first = 0;
		q->rear = -1;
		q->qsize = 0;
		q->max_queue_size = X;

		return q;
}

void Enqueue(Queue* Q, int X) {
		Q->key[qsize] = X;
		Q->rear++;
		Q->qsize++;
}

int Dequeue(Queue* Q) {
		int a = Q->ket[first];
		Q->key[first] = NULL;
		Q->first++;
		Q->qsize--;

		return a;
}*/

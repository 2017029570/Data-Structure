#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

typedef struct HeapStruct {
		int Capacity;
		int Size;
		ElementType *Elements;
}Heap;

Heap* CreateHeap(int heapSize) {
		Heap* heap;
		heap = (Heap*)malloc(sizeof(Heap));
		heap->Capacity = heapSize;
		heap->Size = 0;
		heap->Elements = (int*)malloc(sizeof(int)*(heapSize+1));
		return heap;
}

int Find(Heap *heap, int value) {
		for(int i=1;i<=(heap->Size);i++) {
				if(value == heap->Elements[i]) return 1;
		}
		return 0;
}

void Insert(Heap *heap, int value) {
		if(heap->Size == heap->Capacity) 
				printf("Insertion Error : Max heap is full.\n");
		else if(Find(heap, value) == 1) 
				printf("%d is already in the tree.\n",value);
		else {
				int i;
				for(i = ++heap->Size;heap->Elements[i/2]<value&&i!=1;i/=2)
						heap->Elements[i] = heap->Elements[i/2];
				heap->Elements[i] = value;
				printf("Insert %d.\n",value);
		}
}

int DeleteMax(Heap *heap) {
		if(heap->Size == 0) {
				printf("Deletion Error : Max heap is empty!\n");
				return;
		}
		int i,Child, LastElements, MinElements;
		LastElements = heap->Elements[heap->Size--];
		MinElements = heap->Elements[1];
		for(i=1;i*2<=heap->Size;i=Child) {
				Child = i*2;
				if(Child != heap->Size && heap->Elements[Child]<heap->Elements[Child+1])
						Child++;
				if(LastElements<heap->Elements[Child])
						heap->Elements[i] = heap->Elements[Child];
				else break;
		}
		heap->Elements[i] = LastElements;
		return MinElements;
}

void PrintHeap(Heap *heap) {
		if(heap->Size == 0) {
				printf("Print Error : MAx heap is empty!\n");
				return;
		}
		for(int i=1;i<=heap->Size;i++) {
				printf("%d ",heap->Elements[i]);
		}
		printf("\n");
}

int main(int argc, char* argv[]) {
		FILE *fi = fopen(argv[1], "r");
		char cv;
		Heap* maxHeap;
		int heapSize, key;
		while(!feof(fi)) {
				fscanf(fi, "%c", &cv);
				switch(cv) {
						case 'n':
								fscanf(fi, "%d", &heapSize);
								maxHeap = CreateHeap(heapSize);
								break;
						case 'i':
								fscanf(fi, "%d", &key);
								Insert(maxHeap, key);
								break;
						case 'd':
								DeleteMax(maxHeap);
								break;
						case 'p':
								PrintHeap(maxHeap);
								break;
						case 'f':
								fscanf(fi, "%d", &key);
								if(Find(maxHeap, key))
										printf("%d is in the tree.\n",key);
								else 
										printf("%d is not in the tree.\n", key);
								break;
						}
		}
}

#include <stdio.h>
void swap(int* x, int* y) {
		int p = *y;
		*y = *x;
		*x = p;
}


int main() {
		printf("enter 2 integer\n");
		int a, b;
		scanf("%d %d", &a, &b);

		printf("you entered\n");
		printf("%d %d\n",a,b);

		swap(&a,&b);
		
		printf("after swapping\n");
		printf("%d %d\n",a,b);

		return 0;
}

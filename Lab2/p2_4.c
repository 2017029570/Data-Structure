#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INT_MAX 2147438647

int Zero();
bool IsZero(int x) {
		if(x==0) return true;
		else return false;
}
bool Equal(int x, int y) {
		if(x == y) return true;
		else return false;
}
int Successor(int x) {
		if(x+1<=INT_MAX) return x+1;
		else return x;
}
int Add(int x, int y) {
		if(x+y<=INT_MAX) return x+y;
		else return INT_MAX;
}
int Subtract(int x, int y) {
		if(x>y) return x-y;
		else if(x<y) return 0;
}

int main(int argc, char** argv) {
		int x = atoi(argv[1]);
		int y = atoi(argv[2]);

		printf("Is %d zero? %s\n",x,IsZero(x) ? "True":"False");

		printf("Is %d zero? %s\n",x,IsZero(y) ? "True":"False");
		printf("Does %d equal %d? %s\n",x,y,Equal(x,y) ? "True":"False");
		printf("%d's next number is %d\n",x,Successor(x));
		printf("%d's next number is %d\n",y,Successor(y));
		printf("%d + %d = %d\n", x, y, Add(x,y));
		printf("%d - %d = %d\n", x, y, Subtract(x,y));

		return 0;
}

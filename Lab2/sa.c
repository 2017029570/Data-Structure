#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
		char** name;
		int i;
		int num = atoi(argv[1]);
		printf("enter %d names: ",num);
		name = (char**) malloc(sizeof(char)*31);
		for(i=0;i<num;i++) {
				name[i] = (char*) malloc(sizeof(char)*31);
		}
		for(i=0;i<num;i++) {
				scanf("%s",name[i]);
		}
		for(i=0;i<num;i++) {
				printf("%s\n",name[i]);
		}
		return 0;
}

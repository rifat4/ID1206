#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sem2.h"

int main(){
	init();

	size_t size = rand() % 10 + sizeof(int);

	int *a = dalloc(size);
	//printf("passed\n");
	*a = 25;
	size = rand() % 10 + sizeof(int);
	int *b = dalloc(size);
	*b = 28;
	size = rand() % 10 + sizeof(int);
	int *c = dalloc(size);
	if(a == NULL || b == NULL || c == NULL){
		printf("dalloc failed\n");
	}
	printf("%p\n", a);
	printf("%p\n", b);
	printf("%p\n", c);

	printf("free last\n");
	dfree(c);
	printf("reallocate last\n");
	c = dalloc(27);
	if(c == NULL){printf("dalloc failed\n");}
	printf("%p\n",c);
	return 0;
}

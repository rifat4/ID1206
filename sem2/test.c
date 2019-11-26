#include <stdio.h>
#include <stdlib.h>
#include "sem2.h"

int main(){
	init();

	int *i = dalloc(8);
	//printf("passed\n");
	int *b = dalloc(27);
	int *c = dalloc(27);
	if(b == NULL){
		printf("dalloc failed\n");
	}
	printf("%p\n", i);
	printf("%p\n", b);
	printf("%p\n", c);

	printf("free last\n");
	dfree(c);
	printf("reallocate last\n");
	c = dalloc(27);
	printf("%p\n",c);
	return 0;
}

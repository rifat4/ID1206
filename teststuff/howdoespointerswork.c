#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct head {
	int hej;
	int da;
	uint16_t banan;
};

struct head *after(struct head *block){
	printf("%p\n", block);
	printf("%p\n", (char*)block + sizeof(struct head));
	printf("%ld\n", sizeof(struct head));

	printf("\n%p\n", block + sizeof(struct head));
	return (struct head*)((char*)block + sizeof(struct head));
};
int main(){
	struct head *hea = malloc(sizeof(struct head));
	struct head *next = malloc(sizeof(struct head));
	next->hej = 2;
	hea->hej =1;

	//hea = after(hea);
	printf("this should print 1: %d\n", hea->hej);
	hea = (struct head*)((char*)hea + 0x20);
	printf("%d\n", hea->hej); //should print2;
	printf("%p\n", hea);
	printf("%p\n", next);
	printf("this should print 2 instead of 1: %d\n", hea->hej);
	//free(hea);
	//free(next);

}


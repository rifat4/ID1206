#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct head {
	uint16_t bfree;
	uint16_t bsize;
	uint16_t free;
	uint16_t size;
	struct head *next;
	struct head *prev;
};

struct head* flist;

int main(){
	int i = adjust(5);
	printf("%d\n", i);

	flist = malloc(sizeof(struct head));
	struct head lunez = malloc(sizeof(struct head));

	return 0;
}

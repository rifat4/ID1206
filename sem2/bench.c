#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sem2.h"

#define ROUNDS 10
#define LOOP 1000000

int main() {
	void *init;
	void *current;
	int count = 0;

	printf("The initial top of the heap is %p.\n", init);
	for(int j = 0; j < ROUNDS; j++){

		for(int i = 0; i < LOOP; i++){
			size_t size = (rand() % 4000) + sizeof(int);
			int *memory;
			//printf("count: %d size: %ld\n", count++, size);
			memory = dalloc(size);
			if(memory == NULL){
				fprintf(stderr, "dalloc failed\n");
				return(1);
			}
			*memory = 123;
			dfree(memory);
		}
		current = sbrk(0);
		int allocated = (int) ((current -init) /1024);
		printf("%d\n", j);
		printf("The current top of the heap is %p.\n", current);
		printf("increased by %d Kbyte\n", allocated);
	}

	return 0;
}

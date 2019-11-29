#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "sem2.h"
#include "rand.h"

#define ROUNDS 50
#define LOOP 10

int main() {

	int *memory[LOOP];
	void *init;
	void *current;
	int count = 0;

	printf("The initial top of the heap is %p.\n", init);
	for(int j = 0; j < ROUNDS; j++){
		int limit = rand() % LOOP;
		for(int i = 0; i < limit; i++){
			count++;
			size_t size = (request()) + sizeof(int);
			//printf("count: %d size: %ld\n", count++, size);
			//freeMemory();
			//printf("trying to allocate a block of size %ld\n", size);
			memory[i] = dalloc(size);
			printf("%ld\n", size);
			if(memory[i] == NULL){
				printf("the size of the block we tried to allocate %ld\n", size);
				printf("number of times we have allocated and freed %d\n", (j * LOOP + i));
				freeMemory();
				fprintf(stderr, "dalloc failed\n");
				return(1);
			}
		}

		for(int k = 0; k < rand() % 100; k++){
			for(int i = 0; i < limit; i++){
				*memory[i] = rand() % 100000;
			}
		}

		for(int i = 0; i < limit; i++){
			dfree(memory[i]);
		}
			printf("the size of the block we tried to allocate %d\n", 123);
			printf("number of times we have allocated and freed %d\n", count);
			freeMemory();

	}

	return 0;
}

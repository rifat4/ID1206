#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "sem2.h"

#define ROUNDS 10
#define LOOP 2728


int main() {
	int *memory[LOOP];

	int count = 0;

	for(int j = 0; j < ROUNDS; j++){
		for(int i = 0; i < LOOP; i++){
			size_t size = 8;
			memory[i] = dalloc(size);
			if(memory == NULL){
				fprintf(stderr, "dalloc failed\n");
				return(1);
			}
			*memory[i] = count++;
		}
		for(int i = 0; i < LOOP; i++){
			printf("%d\n", *memory[i]);
			dfree(memory[i]);
		}
		freeMemory();
	}

	return 0;
}

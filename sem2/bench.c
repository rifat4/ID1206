#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "sem2.h"

#define ROUNDS 100000
#define LOOP 10
#define KILO 1000
#define SIZE 16

int main() {

	clock_t begin = clock();

	int *memory[KILO];


	for(int i = 0; i < KILO; i++){
		memory[i] = dalloc(SIZE);
		//printf("count: %d size: %ld\n", count++, size);
		if(memory == NULL){
			fprintf(stderr, "dalloc failed\n");
			return(1);
		}
	}

	for(int k = 0; k < LOOP; k++){
	for(int j = 0; j < ROUNDS; j++){
		for(int i = 0; i < KILO; i++){
			*memory[i] = 123;
		}
	}
	double time_spent = (double)(clock()-begin)/CLOCKS_PER_SEC;
	begin = clock();
	printf("Total time elapsed: %f seconds\n", time_spent);	
	}

	for(int i = 0; i < KILO; i++){
		dfree(memory[i]);
	}

	return 0;
}

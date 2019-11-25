#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PAGES (4096)
#define REFS (1024 * 1024)
#define PAGESIZE (4* 1024)

int main(int argc, char *argv[]){
	clock_t c_start, c_stop;
	printf("#TLB experiment\n");
	printf("# page size = %d bytes\n", (PAGESIZE));
	printf("# max pages = %d\n", (PAGES));
	printf("#total number or references = %d Mi\n", (REFS/(1024*1024)));

	printf("#pages\t proc\t         sum\n");


	for(int pages = 4; pages <= PAGES; pages *=2){
		int loops = REFS / pages;
		c_start = clock();

		long sum = 0;

		char *memory = malloc((long)PAGESIZE * PAGES);

		for(int i = 0; i < loops; i++){
			for(int p = 0; p < pages; p++){
				long ref = (long)p * PAGESIZE;
				memory[ref] += 1;
			}
		}

		c_stop = clock();
		{
			double proc;
			proc = ((double)(c_stop - c_start))/CLOCKS_PER_SEC;
			printf("%d\t %.6f\t %ld\n", pages, proc, sum);
		}
	}
	return 0;
}

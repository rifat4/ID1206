#include <stdlib.h>
#include <sys/mman.h>

#define MAX_HEAP 64*1024*4096

char *heap;

char *brkp = NULL;
char *endp = NULL;

static void init() __attribute__((constructor));

void init() {
	heap = (char *)mmap(NULL, MAX_HEAP,(PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
	brkp = heap;
	endp = brkp + MAX_HEAP;
}

void *sbrk(size_t size){
	if(size == 0){
		return (void *) brkp;
	}
	void *free = (void *) brkp;

	brkp += size;

	if(brkp >= endp){
		return NULL;
	}
	return free;
}


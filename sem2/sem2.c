#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>

#define TRUE 1
#define FALSE 0

#define HEAD (sizeof(struct head))

#define MIN(size) (((size) >(8))?(size):(8))

#define LIMIT(size) (MIN(0) + HEAD + size)

#define MAGIC(memory) ((struct head*)memory - 1)

#define HIDE(block) (void*)((struct head* ) block + 1)

#define ALIGN 8

#define ARENA (64*1024)

struct head {
	uint16_t bfree;
	uint16_t bsize;
	uint16_t free;
	uint16_t size;
	struct head *next;
	struct head *prev;
};

struct head *after(struct head *block) {
	return (struct head*)((char*)block + block->bsize + HEAD);
}

struct head *before(struct head *block) {
	return (struct head*)((char*)block - block->bsize - HEAD);
}

struct head *split (struct head *block, int size){

	//shouldnt it be 8 aligned? uncomment if needed
	//if(size % 8 != 0) size += (8- (size % 8));
	int rsize = block->size - (HEAD + size);
	block->size = size;

	struct head *splt = block + size;
	splt->bsize = block->size;
	splt->bfree = block->free;
	splt->size  = rsize;
	splt->free 	= TRUE; //????

	struct head *aft = block;
	aft->bsize = 0; //not sure what to set it to;

	return splt;
}


struct head *arena = NULL;

struct head *new() {
	if(arena != NULL){
		printf("one arena already allocated \n");
		return NULL;
	}

	struct head *new = mmap(NULL, ARENA,
							PROT_READ | PROT_WRITE,
							MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if(new==MAP_FAILED){
		printf("mmap failed: error %d\n", errno);
		return NULL;
	}

	unsigned int size = ARENA -2*HEAD;

	new->bfree = FALSE;
	new->bsize = 0;	//unsure
	new->free = TRUE;
	new->size = ARENA - 2*HEAD;	//unsure

	struct head *sentinel = after(new); //Dummy head? for circle?
	//After further reading this is to prevent unwanted merging.

	sentinel->bfree = TRUE;
	sentinel->bsize = ARENA - 2*HEAD;
	sentinel->free = FALSE;
	sentinel->size = 0;

	arena = (struct head*)new;

	return new;
}

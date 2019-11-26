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

//checks that our freelist is doubly linked correctly && multiple of Align
//Checks if they are free too.
void sanity(struct head *list){
	struct head *temp;
	temp = list;
	while(temp != NULL){
		if(temp != list->next->prev)"failed sanity check, ->next->prev != this.head";
		if(temp->size % ALIGN != 0)"failed sanity check, not aligned";
		if(temp->free != TRUE)"failed sanity check, not free";
		temp = temp->next;
	}
}

struct head *after(struct head *block) {
	return (struct head*)((char*)block + HEAD + block->size);
}

struct head *before(struct head *block) {
	return (struct head*)((char*)block - block->bsize - HEAD);
}



struct head *flist;

//hard to read maybe redo, but should work
void detach(struct head *block) {
	if(block->prev != NULL){
		if(block->next != NULL){
			block->prev->next = block->next;
			block->next->prev = block->prev;
		} else {
			block->prev->next = NULL;
			block->prev = NULL;
		}
	} else {
		if(block->next != NULL){
			block->next->prev = NULL;
			flist = block->next;
			block->next = NULL;
		} else {
			block = NULL;
			flist = NULL;
		}
	}
	block = NULL;
}

void insert(struct head *block) {
	block -> next = flist;
	block -> prev = NULL;
	if(flist != NULL){
		flist->prev = block;
	}
	flist = block;
}


struct head *split (struct head *block, int size){

	//shouldnt it be 8 aligned? uncomment if needed
	//if(size % 8 != 0) size += (8- (size % 8));
	//its I from the future, we align the size before calling split big brain strats
	int rsize = block->size - (HEAD + size); //new size of block
	block->size = rsize;
	//printf("size : %d\n", size);
	//printf("this is fine\n");

	struct head *splt = (struct head*)((char*)block + rsize);
	splt->bsize = rsize;
	splt->bfree = block->free;
	splt->size  = size;
	splt->free 	= TRUE; //????
	//printf("this\n");
	struct head *aft = after(block);
	aft->bsize = splt->size; //not sure what to set it to, why not just block->next->bsize?

	//*************************************CHANGES*******************************
	//printf("--test\n");
	insert(block);
	//*************************************CHANGES*******************************

	printf("first addr %p\n", block);
	printf("second addr %p\n", splt);
	return splt;
}


struct head *arena = NULL;

struct head *new() {

	//printf("should be written once");
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

	new->next = sentinel;
	new->prev = NULL;
	sentinel->prev = new;
	sentinel->next = NULL;

	arena = (struct head*)new;

	return new;
}

struct head* find(size_t size){
	struct head* temp = flist;
	//printf("flist %p\n", flist);
	while(temp != NULL){
		//printf("flist->size: %d \n",flist->size);
		if(size <= flist->size){
			int tempInt = flist->size;
			detach(temp);
			if(size + 32 <= tempInt){
				temp = split(temp, size);
				return temp;
			} else {
				return temp;
			}
		}
		temp = temp->next;
	}
	return NULL;
}

int adjust(size_t request){
	//printf("request + (ALIGN - request mod ALIGN): %ld\n", request + (ALIGN - request % ALIGN));
	if((request % ALIGN) == 0){ return request;}
	return request + (ALIGN - request % ALIGN);
}


void *dalloc(size_t request){
	if(request <= 0){
		return NULL; //or 0
	}
	int size = adjust(request);
	struct head *taken = find(size);
	if(taken == NULL){ 
		printf("taken == NULL\n");
		return NULL;
	}
	else {
		taken->free = FALSE;
		//printf("debug1\n");
		after(taken)->bfree = FALSE;
		return (void*)taken + HEAD;
	}
}

void dfree(void *memory){
	if(memory != NULL){
		struct head *block = memory - HEAD;
		struct head *aft = after(block); //still have no clue of what to do with aft;
										//we smart now, now we know
		block->free = TRUE;
		aft->bfree = TRUE;
		insert(block);
	}
	return;
}

void init(){
	flist = new();
}

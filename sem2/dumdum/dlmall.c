#include <stdlib.h>


void *dalloc(size_t request){
	if(request <= 0){
		return NULL; //or 0
	}
	int size = adjust(request);
	struct head *taken = find(size);
	if(taken == NULL){ return NULL;}
	else { return (void*)taken;}
}

void dfree(void *memory){
	if(memory != NULL){
		struct head *block = memory;
		struct head *aft = memory->next; //still have no clue of what to do with aft;
		block->free = TRUE;
		aft->bfree = TRUE;

	}
	return;
}

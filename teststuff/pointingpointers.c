#include <stdlib.h>
#include <stdio.h>

struct head {
	int value;
	struct head* next;
	struct head* prev;
};

void detach(struct head* block){
	struct head* temp = NULL;
	if(block->next != NULL){
		if(block-> prev != NULL){
			block->prev->next = block->next;
			block->next->prev = block->prev;
		} else {
			return;
		}
	}
}

int main(){
	struct head* playArea = malloc(2000);
	struct head* domingo = malloc(sizeof(struct head));
	struct head* lunes = malloc(sizeof(struct head));
	domingo->prev = playArea;
	domingo->next = lunes;
	domingo->value = 25;
	lunes->value = 15;
	playArea->next = domingo;
	detach(domingo);
	printf("%d\n",playArea->next->value);
	
	free(playArea);
}

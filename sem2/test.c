#include <stdio.h>
#include <stdlib.h>

int main(){
	void *pointer;

	printf("sizeof pointer %ld\n", sizeof(pointer));
	printf("sizeof addr    %ld should obvious be same as sizeof pointer\n", sizeof(&pointer));
}

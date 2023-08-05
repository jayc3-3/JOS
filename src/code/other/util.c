#include <util.h>

void mem_copy(char* src, char* dst, int bytes){
	for(int i = 0; i < bytes; i++){
		*(dst+i) = *(src+i);
	}
	
	return;
}
#include <ports.h>

void ports_byteOut(unsigned short port, unsigned char data){
	asm ("out %%al, %%dx" : : "a" (data), "d"(port));
	return;
}

void ports_wordOut(unsigned short port, unsigned short data){
	asm ("out %%ax, %%dx" : : "a" (data), "d"(port));
	return;
}

unsigned char ports_byteIn(unsigned short port){
	unsigned char data;
	asm ("in %%dx, %%al" : "=a" (data) : "d"(port));
	return data;
}

unsigned short ports_wordIn(unsigned short port){
	unsigned char data;
	asm ("in %%dx, %%ax" : "=a" (data) : "d"(port));
	return data;
}
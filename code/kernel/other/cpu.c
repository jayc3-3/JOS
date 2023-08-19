#include <cpu.h>

void cpu_byte_out(unsigned short port, unsigned char data){
	asm("out %%al, %%dx" : : "a"(data), "d" (port));

	return;
}

unsigned char cpu_byte_in(unsigned short port){
	unsigned char data;
	
	asm("in %%dx, %%al" : "=a" (data) : "d" (port));
	
	return data;
}

void cpu_word_out(unsigned short port, unsigned short data){
	asm("out %%ax, %%dx" : : "a"(data), "d" (port));

	return;
}

unsigned short cpu_word_in(unsigned short port){
	unsigned short data;
	
	asm("in %%dx, %%ax" : "=a" (data) : "d" (port));
	
	return data;
}

void cpu_wait(void){
	cpu_byte_out(0x80, 0x00);
	
	return;
}

void cpu_cpuid(int code, int* eax, int* ebx, int* ecx, int* edx){
	asm("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(code) :);
	
	return;
}

char* cpu_get_vendor_string(char* string){
	int eax, ebx, ecx, edx;
	
	cpu_cpuid(0, &eax, &ebx, &ecx, &edx);
	string[0] = (char)ebx;
	string[1] = (char)(ebx >> 8);
	string[2] = (char)(ebx >> 16);
	string[3] = (char)(ebx >> 24);
	string[4] = (char)edx;
	string[5] = (char)(edx >> 8);
	string[6] = (char)(edx >> 16);
	string[7] = (char)(edx >> 24);
	string[8] = (char)ecx;
	string[9] = (char)(ecx >> 8);
	string[10] = (char)(ecx >> 16);
	string[11] = (char)(ecx >> 24);
	string[12] = '\n';
	string[13] = '\0';
	
	return string;
}
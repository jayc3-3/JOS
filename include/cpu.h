#ifndef _PORTS_H
#define _PORTS_H

void cpu_byte_out(unsigned short port, unsigned char data);
unsigned char cpu_byte_in(unsigned short port);
void cpu_word_out(unsigned short port, unsigned short data);
unsigned short cpu_word_in(unsigned short port);

void cpu_wait(void);

void cpu_cpuid(int code, int* eax, int* ebx, int* ecx, int* edx);
char* cpu_get_vendor_string(char* string);

#endif
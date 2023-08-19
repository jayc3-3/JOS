#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

typedef struct {
	unsigned short offset_low;
	unsigned short segment;
	unsigned char reserved;
	unsigned char attributes;
	unsigned short offset_high;
}__attribute__((packed)) idt_gate;

typedef struct {
	unsigned short size;
	unsigned int offset;
}__attribute__((packed)) idt_register;

struct registers {
	unsigned int reserved, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_num, err_num;
	unsigned int eip, cs, efl, uesp, ss;
};

void idt_set(int gate, unsigned char attributes, unsigned short segment, void (*base)(struct registers*));
void idt_load(void);

void isr_install(int index, void (*isr)(struct registers*));
void isr_init(void);

#endif
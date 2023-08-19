#include <bool.h>
#include <interrupts.h>
#include <cpu.h>
#include <pic.h>

idt_gate idt[256];
idt_register idtr;

void idt_set(int gate, unsigned char attributes, unsigned short segment, void (*base)(struct registers*)){
	idt[gate] = (idt_gate){
		.offset_low = (unsigned int)base & 0xFFFF,
		.segment = segment,
		.reserved = 0x00,
		.attributes = attributes | 0x60,
		.offset_high = ((unsigned int)base >> 16) & 0xFFFF
	};
	
	return;
}

void idt_load(void){
	idtr.size = sizeof(idt) - 1;
	idtr.offset = (unsigned int)&idt;
	
	asm("lidt (%%eax)" : :"a"(&idtr) :);
	
	return;
}

#include <multiboot.h>
#include <console.h>

char* exception_messages[32] = {
    "Divide by zero",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "OOB",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unrecognized interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED"
};

void exception_handler(struct registers* regs){
	console_active = true;
	console_clear();
	console_printe("Exception recieved\n");
	console_printe(exception_messages[regs->int_num]);
	
	start_halt:
	asm("cli");
	asm("hlt");
	goto start_halt;
}

extern void isr0(struct registers*);
extern void isr1(struct registers*);
extern void isr2(struct registers*);
extern void isr3(struct registers*);
extern void isr4(struct registers*);
extern void isr5(struct registers*);
extern void isr6(struct registers*);
extern void isr7(struct registers*);
extern void isr8(struct registers*);
extern void isr9(struct registers*);
extern void isr10(struct registers*);
extern void isr11(struct registers*);
extern void isr12(struct registers*);
extern void isr13(struct registers*);
extern void isr14(struct registers*);
extern void isr15(struct registers*);
extern void isr16(struct registers*);
extern void isr17(struct registers*);
extern void isr18(struct registers*);
extern void isr19(struct registers*);
extern void isr20(struct registers*);
extern void isr21(struct registers*);
extern void isr22(struct registers*);
extern void isr23(struct registers*);
extern void isr24(struct registers*);
extern void isr25(struct registers*);
extern void isr26(struct registers*);
extern void isr27(struct registers*);
extern void isr28(struct registers*);
extern void isr29(struct registers*);
extern void isr30(struct registers*);
extern void isr31(struct registers*);
extern void isr32(struct registers*);
extern void isr33(struct registers*);
extern void isr34(struct registers*);
extern void isr35(struct registers*);
extern void isr36(struct registers*);
extern void isr37(struct registers*);
extern void isr38(struct registers*);
extern void isr39(struct registers*);
extern void isr40(struct registers*);
extern void isr41(struct registers*);
extern void isr42(struct registers*);
extern void isr43(struct registers*);
extern void isr44(struct registers*);
extern void isr45(struct registers*);
extern void isr46(struct registers*);
extern void isr47(struct registers*);

static void (*isr_stubs[48])(struct registers*) = {
	isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7,
	isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
	isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
	isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31,
	isr32, isr33, isr34, isr35, isr36, isr37, isr38, isr39,
	isr40, isr41, isr42, isr43, isr44, isr45, isr46, isr47
};

static void (*isrs[48])(struct registers*) = {0};

void isr_install(int index, void (*isr)(struct registers*)){
	isrs[index] = isr;
	
	return;
}

void isr_handler(struct registers* regs){
	if(isrs[regs->int_num])
		isrs[regs->int_num](regs);
	
	if(regs->int_num > 31)
		pic_eoi(regs->int_num);
	
	return;
}

void isr_init(void){
	for(int i = 0; i < 48; i++){
		idt_set(i, 0x8E, 0x08, isr_stubs[i]);
	}
	for(int i = 0; i < 32; i++){
		isr_install(i, exception_handler);
	}
	
	return;
}
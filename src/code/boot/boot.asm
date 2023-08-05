MODALIGN equ 1 << 0
MEMINFO  equ 1 << 1
GRAPHICS equ 1 << 2
MBFLAGS  equ MODALIGN | MEMINFO | GRAPHICS
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
dd MAGIC
dd MBFLAGS
dd CHECKSUM

dd 0, 0, 0, 0, 0

dd 0
dd 1280
dd 720
dd 32

section .bss
align 16
stackBottom:
resb 16384
stackTop:

section .text
global _start:function (_start.end - _start)
extern JOSkernel
_start:

mov esp, stackTop
cli

cmp eax, 0x2BADB002
jne .hang

lgdt[gdt.descriptor]

push ebx
call JOSkernel

.hang:
cli
hlt
jmp .hang

.end:

%include "code/boot/gdt.asm"
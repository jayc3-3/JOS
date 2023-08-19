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
dd 1024
dd 768
dd 32

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global kernel_entry:function (kernel_entry.end - kernel_entry)
extern jos_kernel
kernel_entry:

cmp eax, 0x2BADB002
jne .hang

mov ebp, stack_bottom
mov esp, stack_top

lgdt[gdt.descriptor]
jmp gdt.codeseg:.reloadCS

.reloadCS:
mov ax, gdt.dataseg
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax

push ebx
call jos_kernel

.hang:
cli
hlt
jmp .hang

.end:

%include "code/boot/gdt.asm"
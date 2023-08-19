extern isr_handler

isr_common:
pusha
push ds
push es
push fs
push gs

mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
cld

push esp
call isr_handler
add esp, 4

pop gs
pop fs
pop es
pop ds
popa

add esp, 8
iret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39
global isr40
global isr41
global isr42
global isr43
global isr44
global isr45
global isr46
global isr47

isr0:
cli
push 0
push 0
jmp isr_common

isr1:
cli
push 0
push 1
jmp isr_common

isr2:
cli
push 0
push 2
jmp isr_common

isr3:
cli
push 0
push 3
jmp isr_common

isr4:
cli
push 0
push 4
jmp isr_common

isr5:
cli
push 0
push 5
jmp isr_common

isr6:
cli
push 0
push 6
jmp isr_common

isr7:
cli
push 0
push 7
jmp isr_common

isr8:
cli
push 8
jmp isr_common

isr9:
cli
push 0
push 9
jmp isr_common

isr10:
cli
push 10
jmp isr_common

isr11:
cli
push 11
jmp isr_common

isr12:
cli
push 12
jmp isr_common

isr13:
cli
push 13
jmp isr_common

isr14:
cli
push 14
jmp isr_common

isr15:
cli
push 0
push 15
jmp isr_common

isr16:
cli
push 0
push 16
jmp isr_common

isr17:
cli
push 0
push 17
jmp isr_common

isr18:
cli
push 0
push 18
jmp isr_common

isr19:
cli
push 0
push 19
jmp isr_common

isr20:
cli
push 0
push 20
jmp isr_common

isr21:
cli
push 0
push 21
jmp isr_common

isr22:
cli
push 0
push 22
jmp isr_common

isr23:
cli
push 0
push 23
jmp isr_common

isr24:
cli
push 0
push 24
jmp isr_common

isr25:
cli
push 0
push 25
jmp isr_common

isr26:
cli
push 0
push 26
jmp isr_common

isr27:
cli
push 0
push 27
jmp isr_common

isr28:
cli
push 0
push 28
jmp isr_common

isr29:
cli
push 0
push 29
jmp isr_common

isr30:
cli
push 0
push 30
jmp isr_common

isr31:
cli
push 0
push 31
jmp isr_common

isr32:
cli
push 0
push 32
jmp isr_common

isr33:
cli
push 0
push 33
jmp isr_common

isr34:
cli
push 0
push 34
jmp isr_common

isr35:
cli
push 0
push 35
jmp isr_common

isr36:
cli
push 0
push 36
jmp isr_common

isr37:
cli
push 0
push 37
jmp isr_common

isr38:
cli
push 0
push 38
jmp isr_common

isr39:
cli
push 0
push 39
jmp isr_common

isr40:
cli
push 0
push 40
jmp isr_common

isr41:
cli
push 0
push 41
jmp isr_common

isr42:
cli
push 0
push 42
jmp isr_common

isr43:
cli
push 0
push 43
jmp isr_common

isr44:
cli
push 0
push 44
jmp isr_common

isr45:
cli
push 0
push 45
jmp isr_common

isr46:
cli
push 0
push 46
jmp isr_common

isr47:
cli
push 0
push 47
jmp isr_common
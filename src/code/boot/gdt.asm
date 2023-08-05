BITS 32

gdt:
.null:
dq 0

.code:
dw 0xFFFF
dw 0
db 0
db 0b10011010
db 0b11001111
db 0

.data:
dw 0xFFFF
dw 0
db 0
db 0b10010010
db 0b11001111
db 0

.end:

.descriptor:
dw .end - gdt - 1
dd gdt

.codeseg: equ .code - gdt
.dataseg: equ .data - gdt
gdt:
.descriptor:
dw gdt.end - gdt - 1
dd gdt
dw 0

.code:
dw 0xFFFF
dw 0
db 0
db 10011010b
db 11001111b
db 0

.data:
dw 0xFFFF
dw 0
db 0
db 10010010b
db 11001111b
db 0

.codeseg: equ .code - gdt
.dataseg: equ .data - gdt

.end:
```
       ______  _____
      / / __ \/ ___/
 __  / / / / /\__ \ 
/ /_/ / /_/ /___/ / 
\____/\____//____/  
                    
```
Ever wanted to use DOS, but made by an amatuer and barely functional?
Well, this is the thing for you!

## Features:
It does nothing useful or practical!

(That counts as a feature, right?)

## How to run:
### QEMU:

1. Download latest .iso from "releases"

2. Install QEMU

3. Run 'qemu-system-i386 -drive media=cdrom,format=raw,file=JOS.iso' from the command line

### Real hardware:
1. Download latest .iso from "releases"

2. Flash .iso to media of your choice

3. Boot from medium

### Dependencies: (for building from source)
The NASM assembler

GCC and Binutils compiled to the 'i686-elf' target (see [here](https://wiki.osdev.org/GCC_Cross-Compiler) for more info)

Limine

Make

After those are installed, just run the makefile!

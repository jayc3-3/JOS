```
       ______  _____
      / / __ \/ ___/
 __  / / / / /\__ \ 
/ /_/ / /_/ /___/ / 
\____/\____//____/  
                    
```
Ever wanted to use DOS, but made by an amatuer and barely functional?
Well, this is the thing for you!

## How to run:
### QEMU:
1. Download latest .iso from "releases"

2. Install QEMU

3. Run 'qemu-system-i386 -drive media=cdrom,format=raw,file=JOS.iso' from the command line

### Real hardware:
#### USB:
1. Download latest .iso from "releases"

2. Flash .iso to drive

3. Boot from USB

#### CDROM:
1. Download latest .iso from "releases"

2. Burn .iso to CD

3. Boot from CD

### Dependencies: (for building from source)
The NASM assembler

GCC and Binutils compiled to the 'i686-elf' target (see [here](https://wiki.osdev.org/GCC_Cross-Compiler) for more info)

The 'grub-pc-bin' package

Make

After those are installed, just run the makefile!

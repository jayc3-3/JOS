```
_________ _______  _______ 
\__    _/(  ___  )(  ____ \
   )  (  | (   ) || (    \/
   |  |  | |   | || (_____ 
   |  |  | |   | |(_____  )
   |  |  | |   | |      ) |
|\_)  )  | (___) |/\____) |
(____/   (_______)\_______)
```
Ever wanted to use DOS, but made by an amatuer and barely functional?
Well, this is the thing for you!

## How to run:
### QEMU:
1. Download latest .iso from "releases"

2. Install QEMU

3. Run 'qemu-system-i386 -drive media=cdrom,format=raw,file=JOS.iso' from the command line

### Real hardware:
1. Download latest .bin from "releases" (or .iso when using cd's)

2. Flash it to a USB drive (or any other media)

3. Launch from your systems boot manager (varies on different computers)

### Dependencies: (for building from source)
The NASM assembler

GCC and Binutils compiled to the 'i686-elf' target (see [here](https://wiki.osdev.org/GCC_Cross-Compiler) for more info)

The 'grub-pc-bin' package

Make

After those are installed, just run the makefile!

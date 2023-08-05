```
       __ ____  _____
      / // __ \/ ___/
 __  / // / / /\__ \ 
/ /_/ // /_/ /___/ / 
\____/ \____/ \___/  
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
#### USB:
1. Download 'JOSusb.zip' from "releases"

2. Unzip the contents of the .zip file onto a FAT32 formatted USB

3. Launch using your systems boot manager

#### ISO:
1. Download latest .iso from "releases"

2. Flash to USB drive or burn onto CDROM

3. Launch using your systems boot manager

### Dependencies: (for building from source)
The NASM assembler

GCC and Binutils compiled to the 'i686-elf' target (see [here](https://wiki.osdev.org/GCC_Cross-Compiler) for more info)

Limine

Make

After those are installed, just run the makefile to either the 'usb' or 'iso' target

![image](https://github.com/jayc3-3/JOS/assets/85657500/9c63f153-1bf5-4c5f-bf2e-08e7e5ae4421)

Ever wanted to use DOS, but made by an amatuer and barely functional?
Well, this is the thing for you!

## Features:
Framebuffer Graphics

PS/2 Keyboard Input

(That's it.)

## System Requirements:
- An i686-compatible CPU
- At least 16MiB of RAM
- A GPU that can output 720p
- LBA48-compliant hard drive

(Basically anything that's made after the 2000s)

## How to run:
### QEMU:
1. Download latest .iso from "releases"

2. Install QEMU

3. Run 'qemu-system-i386 -drive media=cdrom,format=raw,file=JOS.iso' from the command line

### VirtualBox:
1. Download latest .iso from "releases"

2. Install VirtualBox

3. Create new virtual machine with type 'Other' and version 'Other/Unknown'

### Real hardware:
#### USB:
1. Download 'JOSusb.zip' from "releases"

2. Unzip the contents of the .zip file onto a FAT32 formatted USB

3. (If not using a UEFI system) Run 'make usb' with the path to your USB drive (on linux this will be something like /dev/sdx)

4. Launch using your systems boot manager

#### ISO:
1. Download latest .iso from "releases"

2. Flash to USB drive or burn onto CDROM

3. Launch using your systems boot manager

##### Note for running on real hardware
Fails to boot with secure boot enabled, but that may vary based on hardware

### Dependencies (for building from source)
The NASM assembler

GCC and Binutils compiled to the 'i686-elf' target (see [here](https://wiki.osdev.org/GCC_Cross-Compiler) for more info)

Limine

Make

Xorriso

After those are installed, just run the makefile to either the 'usb' or 'iso' target

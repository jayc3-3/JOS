# JOS - Janky Operating System
Ever wanted to use DOS, but made by an amatuer and only half functional?
Well, this is the thing for you!

How to run:
QEMU:
Download latest .iso from "releases"
Install QEMU
Run 'qemu-system-i386 -drive media=cdrom,format=raw,file=JOS.iso' from the command line

Real hardware:
Download latest .iso from "releases"
Flash it to a USB (or any other media)
Launch from your systems boot manager (varies on different computers)

Dependencies: (for building from source)
NASM
GCC and Binutils compiled to the 'i686-elf' target (see [here](wiki.osdev.org) for more info)
The 'grub-pc-bin' package
Make

After those are installed, just run the makefile!

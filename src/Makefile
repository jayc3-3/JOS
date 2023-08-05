ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc
EMU = qemu-system-i386

ASMFLAGS = -felf32
CFLAGS = -ffreestanding -Wall -Iinclude
LDFLAGS =  -T linker.ld -ffreestanding -nostdlib -lgcc
EMUFLAGS = -net none -drive media=cdrom,format=raw,file=

OBJFILES = boot.o kernel.o framebuffer.o string.o math.o console.o
COMPILENAME = JOS-0.0.1

all: iso

clean:
	rm *.o
	rm bootable/boot/${COMPILENAME}.bin

boot.o: code/boot/boot.asm
	${ASM} $< -o $@ ${ASMFLAGS}

kernel.o: code/kernel.c
	${CC} -c $< -o $@ ${CFLAGS}

vga.o: code/graphics/vga.c
	${CC} -c $< -o $@ ${CFLAGS}

framebuffer.o: code/graphics/framebuffer.c
	${CC} -c $< -o $@ ${CFLAGS}

console.o: code/graphics/console.c
	${CC} -c $< -o $@ ${CFLAGS}

util.o: code/other/util.c
	${CC} -c $< -o $@ ${CFLAGS}

string.o: code/other/string.c
	${CC} -c $< -o $@ ${CFLAGS}

math.o: code/other/math.c
	${CC} -c $< -o $@ ${CFLAGS}

JOS.bin: ${OBJFILES}
	${LD} $^ -o ${COMPILENAME}.bin ${LDFLAGS}

iso: JOS.bin
	mv ${COMPILENAME}.bin bootable/boot
	xorriso -as mkisofs -b /boot/limine-bios-cd.bin \
			-no-emul-boot -boot-load-size 4 -boot-info-table \
			--efi-boot /boot/limine-uefi-cd.bin -efi-boot-part \
			--efi-boot-image --protective-msdos-label \
			bootable -o ${COMPILENAME}.iso
	limine bios-install ${COMPILENAME}.iso

usb: JOS.bin
	mv ${COMPILENAME}.bin bootable/boot

run: iso
	${EMU} ${EMUFLAGS}${COMPILENAME}.iso
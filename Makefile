ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc

ASMFLAGS = -felf32
CFLAGS = -ffreestanding -Iinclude
LDFLAGS = -T linker.ld -ffreestanding -nostdlib -lgcc

OBJFILES = temp/boot.o temp/kernel.o temp/cpu.o temp/pic.o temp/string.o temp/interrupts.o temp/isr.o temp/framebuffer.o temp/graphics.o temp/console.o temp/ps2.o temp/ps2_keyboard.o
COMPILENAME = JOS-0.0.2

all: JOS.bin

clean:
	rm temp/*.o

temp/boot.o: code/boot/boot.asm
	${ASM} $< -o $@ ${ASMFLAGS}

temp/kernel.o: code/kernel/kernel.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/cpu.o: code/kernel/other/cpu.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/pic.o: code/kernel/other/pic.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/string.o: code/kernel/other/string.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/interrupts.o: code/kernel/other/interrupts.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/isr.o: code/kernel/other/isr.asm
	${ASM} $< -o $@ ${ASMFLAGS}

temp/framebuffer.o: code/kernel/graphics/framebuffer.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/graphics.o: code/kernel/graphics/graphics.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/console.o: code/kernel/graphics/console.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/ps2.o: code/kernel/hardware/ps2.c
	${CC} -c $< -o $@ ${CFLAGS}

temp/ps2_keyboard.o: code/kernel/hardware/ps2_keyboard.c
	${CC} -c $< -o $@ ${CFLAGS}

JOS.bin: ${OBJFILES}
	${LD} $^ -o ${COMPILENAME}.bin ${LDFLAGS}

iso: JOS.bin
	mv ${COMPILENAME}.bin bootable/boot/JOS.bin
	xorriso -as mkisofs -b /boot/limine-bios-cd.bin \
			-no-emul-boot -boot-load-size 4 -boot-info-table \
			--efi-boot /boot/limine-uefi-cd.bin -efi-boot-part \
			--efi-boot-image --protective-msdos-label \
			bootable -o ${COMPILENAME}.iso
	limine bios-install ${COMPILENAME}.iso

usb: JOS.bin
	mv ${COMPILENAME}.bin bootable/boot/JOS.bin
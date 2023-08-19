#ifndef _PIC_H
#define _PIC_H

#define MPIC_COM 0x20
#define MPIC_DAT 0x21
#define SPIC_COM 0xA0
#define SPIC_DAT 0xA1

void pic_remap(int master_offset, int slave_offset);
void pic_set_mask(unsigned char line);
void pic_clear_mask(unsigned char line);

void pic_eoi(unsigned char irq);

#endif
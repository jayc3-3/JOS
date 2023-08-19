#ifndef _PS2_H
#define _PS2_H

#define PS2_DAT  0x60
#define PS2_COM  0x64
#define PS2_STAT 0x64

extern bool ps2;
extern bool ps2_port1;
extern bool ps2_port2;

bool ps2_init(void);

void ps2_byte_out(unsigned short port, unsigned char data);
unsigned char ps2_byte_in(unsigned short port);

#endif
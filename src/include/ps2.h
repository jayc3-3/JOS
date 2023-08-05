#ifndef _PS2_H
#define _PS2_H

#define PS2_DATA    0x60
#define PS2_STATUS  0x64
#define PS2_COMMAND 0x64

int ps2_init(void);

unsigned char ps2_readPort(unsigned short port);
void ps2_sendPort(unsigned short port, unsigned char data);

#endif
#ifndef _PORTS_H
#define _PORTS_H

void ports_byteOut(unsigned short port, unsigned char data);
void ports_wordOut(unsigned short port, unsigned short data);

unsigned char ports_byteIn(unsigned short port);
unsigned short ports_wordIn(unsigned short port);

#endif
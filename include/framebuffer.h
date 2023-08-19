#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

void framebuffer_put(unsigned int* memory, int pitch, int x, int y, int color);
void framebuffer_put_rect(unsigned int* memory, int pitch, int x, int y, int w, int h, int color);

#endif
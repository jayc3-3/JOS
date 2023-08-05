#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

void fb_init(unsigned long long framebufferAddr, int pitch, int colorDepth, int width, int height);

void fb_clearScreen(int color);

void fb_drawRect(int x, int y, int w, int h, int color);
void fb_drawChar(char c, int x, int y, int color);

#endif
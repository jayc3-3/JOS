#ifndef _GRAPHICS_H
#define _GRAPHICS_H

extern int graphics_width;
extern int graphics_height;
extern int graphics_pitch;
extern int graphics_bpp;

bool graphics_init(multiboot_info_t* multiboot_info);

void graphics_clear(int color);
void graphics_rect(int x, int y, int w, int h, int color);
bool graphics_putc(char c, int x, int y, int scale, int color);

#endif